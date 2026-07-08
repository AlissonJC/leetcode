/*
 * LeetCode 855 - Exam Room
 *
 * A row of n seats is labeled 0..n-1. A student entering sits at the empty seat that
 * maximizes the distance to the closest already-seated student; ties are broken by the
 * lowest seat number, and an empty room seats the student at 0. Design a class supporting:
 *   - ExamRoom(int n): create a room with n seats.
 *   - int  seat():     seat the next student and return their seat label.
 *   - void leave(int p): the student at seat p (guaranteed present) leaves.
 *
 * Input/Output: method calls as above; seat() returns an int seat label, leave() returns
 *   nothing. (No stdin/stdout — LeetCode drives the class directly.)
 *
 * Constraints: 1 <= n <= 1e9, at most 1e4 calls to seat/leave combined, leave(p) always
 *   targets an occupied seat.
 *
 * Approach: n can be a billion, but there are at most 1e4 students, so store only the
 *   OCCUPIED seats in an ordered set. For seat(), the best empty seat is one of:
 *     - seat 0, whose closest-person distance equals the first occupied seat's index;
 *     - the midpoint of each gap between two consecutive occupied seats a < b, giving
 *       distance (b - a) / 2 at seat a + (b - a) / 2;
 *     - seat n-1, whose distance equals (n-1) minus the last occupied seat.
 *   Scan these candidates left to right (seat 0, then interior midpoints in increasing
 *   order, then seat n-1) and keep the best, replacing only on a STRICTLY greater distance.
 *   Because the candidate seat labels are produced in increasing order, strict-greater
 *   automatically yields the lowest label among equal-distance ties. An empty room returns 0.
 *   leave(p) is a set erase.
 *
 * Complexity: seat() is O(k) (scan the k occupied seats), leave() is O(log k), where k is
 *   the current number of students (<= 1e4). Space O(k). Seat labels fit in int (< 1e9).
 */

#include <set>
using namespace std;

class ExamRoom {
    int n;
    set<int> occupied;                       // labels of currently occupied seats, ascending

public:
    ExamRoom(int n) : n(n) {}

    int seat() {
        if (occupied.empty()) {              // empty room -> the rule fixes seat 0
            occupied.insert(0);
            return 0;
        }

        // Candidate 1: sit at seat 0; closest person is the first occupied seat.
        int bestSeat = 0;
        int bestDist = *occupied.begin();

        // Candidate 2: the midpoint of every interior gap between consecutive occupants.
        int prev = -1;
        for (int s : occupied) {
            if (prev != -1) {
                int d = (s - prev) / 2;      // distance the midpoint achieves in this gap
                if (d > bestDist) {          // strict '>' keeps the lowest label on ties
                    bestDist = d;
                    bestSeat = prev + d;
                }
            }
            prev = s;
        }

        // Candidate 3: sit at the last seat; closest person is the last occupied seat.
        int d = (n - 1) - *occupied.rbegin();
        if (d > bestDist) {
            bestDist = d;
            bestSeat = n - 1;
        }

        occupied.insert(bestSeat);
        return bestSeat;
    }

    void leave(int p) {
        occupied.erase(p);                   // p is guaranteed to be occupied
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
