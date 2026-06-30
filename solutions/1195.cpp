/*
 * LeetCode 1195 - Fizz Buzz Multithreaded
 *
 * A FizzBuzz(n) instance is shared by four threads that together print the FizzBuzz
 * sequence for 1..n in order: number() prints i when i is divisible by neither 3 nor 5,
 * fizz() prints "fizz" when i is divisible by 3 but not 5, buzz() prints "buzz" when
 * divisible by 5 but not 3, and fizzbuzz() prints "fizzbuzz" when divisible by both.
 *
 * Input  : int n; the four methods receive void() / void(int) print callbacks.
 * Output : the callbacks fire so the printed tokens form the FizzBuzz series for 1..n.
 *
 * Constraints: 1 <= n <= 50.
 *
 * Approach: a shared counter `cur` (the next value to print, starting at 1) guarded by a
 *   mutex and condition variable. Each of the four threads loops: it waits until either
 *   cur exceeds n (time to stop) or cur is a value it is responsible for, then prints,
 *   advances cur, and notifies the others. A single helper run(predicate, action) factors
 *   out this loop; the action takes the current value so number() can print it while the
 *   word-printers ignore it. Predicate waits handle spurious wake-ups, and once cur > n
 *   every thread's predicate is satisfied so they all exit cleanly.
 *
 * Complexity: O(n) prints total, each O(1) under the lock; O(1) space.
 */

#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

class FizzBuzz {
    int n;
    int cur = 1;            // next number to print
    mutex m;
    condition_variable cv;

    // Shared loop: wait for a value this thread owns (or termination), print, advance.
    void run(function<bool(int)> owns, function<void(int)> act) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [&] { return cur > n || owns(cur); });
            if (cur > n) break;          // sequence finished
            act(cur);
            ++cur;
            cv.notify_all();             // let the owner of the next value proceed
        }
    }

public:
    FizzBuzz(int n) { this->n = n; }

    void fizz(function<void()> printFizz) {
        run([](int x) { return x % 3 == 0 && x % 5 != 0; }, [&](int) { printFizz(); });
    }

    void buzz(function<void()> printBuzz) {
        run([](int x) { return x % 5 == 0 && x % 3 != 0; }, [&](int) { printBuzz(); });
    }

    void fizzbuzz(function<void()> printFizzBuzz) {
        run([](int x) { return x % 15 == 0; }, [&](int) { printFizzBuzz(); });
    }

    void number(function<void(int)> printNumber) {
        run([](int x) { return x % 3 != 0 && x % 5 != 0; }, [&](int x) { printNumber(x); });
    }
};
