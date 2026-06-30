/*
 * LeetCode 1226 - The Dining Philosophers
 *
 * Five philosophers (ids 0..4, clockwise) share five forks, one between each adjacent
 * pair. Philosopher p needs the fork on its left (id p) and the fork on its right
 * (id (p+1)%5) to eat, and a fork can be held by only one philosopher at a time.
 * Implement wantsToEat(p, pickLeft, pickRight, eat, putLeft, putRight) so that nobody
 * ever deadlocks or starves: each call must pick up both forks, eat, then put both down.
 *
 * Input  : philosopher id p and six action callbacks; called concurrently by 5 threads.
 * Output : the callbacks fire so that picks precede eat, puts follow eat, and no fork is
 *          ever held by two philosophers at once.
 *
 * Constraints: 1 <= n <= 60 calls per philosopher.
 *
 * Approach: give each fork its own mutex. The classic deadlock happens when every
 *   philosopher grabs one fork and waits forever for the other (a circular wait). To
 *   prevent it, acquire BOTH fork mutexes together with std::lock, whose back-off
 *   algorithm guarantees no deadlock regardless of which forks each thread wants. While
 *   both mutexes are held the philosopher picks the forks, eats, and puts them back, so
 *   two philosophers can never hold the same fork simultaneously, while non-adjacent
 *   philosophers can still eat at the same time. lock_guard with adopt_lock releases both
 *   forks when the call returns.
 *
 * Complexity: O(1) work per call (two lock acquisitions and the six callbacks); O(1)
 *   extra space (five fork mutexes).
 */

#include <functional>
#include <mutex>
using namespace std;

class DiningPhilosophers {
    mutex forks[5];           // forks[i] guards the i-th fork

public:
    DiningPhilosophers() {}

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int left = philosopher;            // fork on the left
        int right = (philosopher + 1) % 5; // fork on the right

        // Grab both forks at once; std::lock cannot deadlock even if neighbours
        // request the same pair in a different order.
        lock(forks[left], forks[right]);
        lock_guard<mutex> holdLeft(forks[left], adopt_lock);
        lock_guard<mutex> holdRight(forks[right], adopt_lock);

        // Both forks are now exclusively held: pick up, eat, put down.
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
    }
};
