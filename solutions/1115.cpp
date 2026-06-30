/*
 * LeetCode 1115 - Print FooBar Alternately
 *
 * A single FooBar(n) instance is shared by two threads: one runs foo() (which calls its
 * printFoo callback n times), the other runs bar() (printBar n times). Add
 * synchronization so the combined output is "foobar" repeated n times — i.e. foo and bar
 * strictly alternate, starting with foo.
 *
 * Input  : int n; foo()/bar() each receive a void() callback printing "foo"/"bar".
 * Output : the callbacks fire in the order foo, bar, foo, bar, ... for n rounds.
 *
 * Constraints: 1 <= n <= 1000.
 *
 * Approach: a single boolean fooTurn (true means it is foo's turn) protected by a mutex,
 *   plus a condition variable. Each side loops n times: foo waits until fooTurn is true,
 *   prints, sets fooTurn false and notifies; bar waits until fooTurn is false, prints,
 *   sets it true and notifies. Waiting with a predicate re-checks the flag on every
 *   wake-up, so spurious wake-ups and the unknown thread start order are both handled,
 *   and the two sides hand the turn back and forth exactly n times.
 *
 * Complexity: O(n) prints total, each guarded by O(1) lock/wait work; O(1) space.
 */

#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

class FooBar {
    int n;
    mutex m;
    condition_variable cv;
    bool fooTurn = true;        // foo goes first

public:
    FooBar(int n) { this->n = n; }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; ++i) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this] { return fooTurn; });   // wait for foo's turn
            printFoo();
            fooTurn = false;                             // hand the turn to bar
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; ++i) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this] { return !fooTurn; });  // wait for bar's turn
            printBar();
            fooTurn = true;                              // hand the turn back to foo
            cv.notify_one();
        }
    }
};
