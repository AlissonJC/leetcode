/*
 * LeetCode 1114 - Print in Order
 *
 * A single Foo instance is shared by three threads: one calls first(), one second(),
 * one third(), in an order decided by the OS scheduler. Add synchronization so that the
 * supplied callbacks always run as printFirst -> printSecond -> printThird, no matter how
 * the threads are scheduled.
 *
 * Input  : the three methods each receive a void() callback that prints "first" /
 *          "second" / "third". Output : the callbacks execute in the required order.
 *
 * Constraints: the input permutation of [1,2,3] only labels which thread calls which
 *   method; it does not guarantee call timing, so real synchronization is required.
 *
 * Approach: keep a shared `stage` counter (0 -> 1 -> 2) protected by a mutex, with a
 *   condition variable to block threads until their turn. first() prints immediately and
 *   advances the stage to 1; second() waits until stage >= 1, prints, then advances to 2;
 *   third() waits until stage >= 2 and prints. Using condition_variable::wait with a
 *   predicate re-checks the stage on every wake-up, so spurious wake-ups and any arrival
 *   order are handled correctly. notify_all releases whichever method is waiting next.
 *
 * Complexity: O(1) work per call; each thread blocks at most until its predecessor has
 *   advanced the stage. O(1) space.
 */

#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

class Foo {
    mutex m;
    condition_variable cv;
    int stage = 0;            // 0: none done, 1: first done, 2: second done

public:
    Foo() {}

    void first(function<void()> printFirst) {
        unique_lock<mutex> lock(m);
        printFirst();         // no predecessor, so run right away
        stage = 1;
        cv.notify_all();      // wake second() if it is already waiting
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return stage >= 1; });   // block until first() finished
        printSecond();
        stage = 2;
        cv.notify_all();      // wake third()
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return stage >= 2; });   // block until second() finished
        printThird();
    }
};
