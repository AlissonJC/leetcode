/*
 * LeetCode 1117 - Building H2O
 *
 * Many threads call hydrogen() or oxygen() on a shared H2O instance, each releasing one
 * atom via its callback. The atoms must bond into water molecules of exactly two
 * hydrogens and one oxygen, and every thread of one molecule must release before any
 * thread of the next molecule does. Add synchronization so that, reading the output in
 * groups of three, each group always contains exactly two H and one O.
 *
 * Input  : threads calling hydrogen(releaseHydrogen) / oxygen(releaseOxygen).
 * Output : a sequence of "H"/"O" whose every consecutive triple has two H and one O.
 *
 * Constraints: water has length 3n with 1 <= n <= 20, exactly 2n 'H' and n 'O'.
 *
 * Approach: track how many hydrogens (h, capped at 2) and oxygens (o, capped at 1) have
 *   already released within the CURRENT molecule, guarded by a mutex and condition
 *   variable. A hydrogen waits until h < 2, an oxygen until o < 1; the entire critical
 *   section (wait, release, increment) is held under the lock, so releases are serialized
 *   and at most two H and one O bond per molecule. The moment h == 2 and o == 1, the
 *   molecule is complete, so the counters reset to admit the next one. A thread belonging
 *   to the next molecule can only pass its wait after that reset, which only happens once
 *   the current molecule's third atom has released — that is exactly the required barrier.
 *
 * Complexity: O(1) work per atom (each blocks only until a slot in the current molecule
 *   frees up); O(1) space.
 */

#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

class H2O {
    mutex m;
    condition_variable cv;
    int h = 0;            // hydrogens already released in the current molecule (0..2)
    int o = 0;            // oxygens already released in the current molecule (0..1)

    // Called while holding the lock: if the molecule is full, begin a fresh one.
    void resetIfComplete() {
        if (h == 2 && o == 1) { h = 0; o = 0; }
    }

public:
    H2O() {}

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return h < 2; });   // wait for a hydrogen slot
        releaseHydrogen();                          // "H"
        ++h;
        resetIfComplete();
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return o < 1; });    // wait for the oxygen slot
        releaseOxygen();                            // "O"
        ++o;
        resetIfComplete();
        cv.notify_all();
    }
};
