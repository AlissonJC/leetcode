/*
 * LeetCode 1116 - Print Zero Even Odd
 *
 * A ZeroEvenOdd(n) instance is shared by three threads calling zero(), even(), and
 * odd(), each given a printNumber(int) callback. zero() must print 0 once before every
 * number, even() prints the even numbers, odd() prints the odd numbers, so the combined
 * output is the series 0 1 0 2 0 3 0 4 ... of total length 2n (e.g. "0102030405" for
 * n = 5).
 *
 * Input  : int n; zero()/even()/odd() each receive a void(int) callback.
 * Output : the callbacks fire so the printed digits form "0 k" for k = 1..n in order.
 *
 * Constraints: 1 <= n <= 1000.
 *
 * Approach: a single `turn` state (0 = zero's turn, 1 = odd's turn, 2 = even's turn)
 *   guarded by a mutex and a condition variable. zero() runs n times: it waits for turn
 *   0, prints 0, then passes the turn to odd or even depending on the parity of the
 *   number about to be printed. odd() walks 1, 3, 5, ... and even() walks 2, 4, 6, ...;
 *   each waits for its own turn, prints its current value, and returns the turn to zero.
 *   Because zero hands control to exactly one parity thread per step and they advance
 *   their counters in lockstep with zero, the right value is always printed. Predicate
 *   waits absorb spurious wake-ups; notify_all wakes whichever thread is next.
 *
 * Complexity: O(n) prints, each with O(1) lock/wait work; O(1) space.
 */

#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

class ZeroEvenOdd {
    int n;
    mutex m;
    condition_variable cv;
    int turn = 0;             // 0 = zero, 1 = odd, 2 = even

public:
    ZeroEvenOdd(int n) { this->n = n; }

    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; ++i) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this] { return turn == 0; });
            printNumber(0);
            // The number coming next is i: odd i -> odd thread, even i -> even thread.
            turn = (i % 2 == 1) ? 1 : 2;
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {              // 1, 3, 5, ...
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this] { return turn == 1; });
            printNumber(i);
            turn = 0;                                  // back to zero
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {              // 2, 4, 6, ...
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this] { return turn == 2; });
            printNumber(i);
            turn = 0;                                  // back to zero
            cv.notify_all();
        }
    }
};
