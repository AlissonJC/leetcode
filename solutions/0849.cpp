/*
 * LeetCode 849 - Maximize Distance to Closest Person
 *
 * A row of seats is given as an array where seats[i] = 1 means someone is sitting there and
 * seats[i] = 0 means it is empty. There is at least one person and at least one empty seat.
 * Alex will take an empty seat chosen to maximize the distance to the nearest occupied seat.
 * Return that maximum possible distance.
 *
 * Input  : vector<int> seats (0/1 entries).
 * Output : int — the largest achievable distance from Alex to the closest person.
 *
 * Constraints: 2 <= n <= 2e4, seats[i] in {0,1}, at least one 0 and at least one 1.
 *
 * Approach: The best seat lies inside a maximal run of empty seats, and only three run types
 *   matter. Walk the row remembering the index of the previous person (prev):
 *     - Interior run: empty seats bounded by a person on both sides (at prev and at i). The
 *       optimal seat is the midpoint, giving distance (i - prev) / 2.
 *     - Leading run: empties before the first person. Sitting at seat 0 gives distance equal
 *       to that first person's index.
 *     - Trailing run: empties after the last person. Sitting at the last seat gives distance
 *       (n - 1) - lastPersonIndex.
 *   The answer is the maximum candidate across all runs.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = (int)seats.size();
        int best = 0;
        int prev = -1;                      // index of the most recent person seen (-1 = none yet)

        for (int i = 0; i < n; ++i) {
            if (seats[i] == 1) {
                if (prev == -1)
                    best = max(best, i);            // leading run: distance from seat 0 to first person
                else
                    best = max(best, (i - prev) / 2); // interior run: midpoint of the gap
                prev = i;
            }
        }
        // Trailing run: empties after the last person (prev is guaranteed set — a person exists).
        best = max(best, (n - 1) - prev);
        return best;
    }
};
