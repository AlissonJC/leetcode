/*
 * LeetCode 2037 - Minimum Number of Moves to Seat Everyone
 *
 * There are n seats and n students on a number line, given by their positions in seats[]
 * and students[]. Moving a student one unit left or right costs one move. Assign each
 * student to a distinct seat and return the minimum total moves. Positions may repeat.
 *
 * Input  : vector<int> seats, vector<int> students (equal length n).
 * Output : the minimum total number of moves.
 *
 * Constraints: 1 <= n <= 100; 1 <= seats[i], students[j] <= 100.
 *
 * Greedy: sort both position lists and pair the k-th smallest student with the k-th
 *   smallest seat; the answer is the sum of |seat - student| over those pairs. Exchange
 *   argument: if a matching ever "crosses" (a smaller student takes a larger seat while a
 *   larger student takes a smaller seat), uncrossing them never increases total distance,
 *   so the sorted, non-crossing pairing is optimal.
 *
 * Approach: realize both sorts with counting sort, since positions lie in the fixed range
 *   [1, 100]. Tally each list's value frequencies, rebuild both in ascending order by
 *   emitting every value as many times as it occurs, then walk the two sorted arrays in
 *   lockstep summing absolute differences. No comparison sort is needed.
 *
 * Complexity: O(n + V) time (V = 100 position range), O(n + V) space.
 */

#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        const int MAXP = 100;
        int cs[MAXP + 1] = {0};          // frequency of each seat position
        int ct[MAXP + 1] = {0};          // frequency of each student position
        for (int x : seats)    cs[x]++;
        for (int x : students) ct[x]++;

        // Counting sort: rebuild each list in ascending order.
        vector<int> sortedSeats, sortedStudents;
        sortedSeats.reserve(seats.size());
        sortedStudents.reserve(students.size());
        for (int v = 1; v <= MAXP; ++v) {
            for (int k = 0; k < cs[v]; ++k) sortedSeats.push_back(v);
            for (int k = 0; k < ct[v]; ++k) sortedStudents.push_back(v);
        }

        // Pair k-th smallest with k-th smallest and accumulate the distances.
        int moves = 0;
        for (size_t i = 0; i < sortedSeats.size(); ++i)
            moves += abs(sortedSeats[i] - sortedStudents[i]);
        return moves;
    }
};
