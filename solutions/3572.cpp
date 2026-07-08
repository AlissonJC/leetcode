/*
 * LeetCode 3572 - Maximize Y-Sum by Picking a Triplet of Distinct X-Values
 *
 * Given two integer arrays x and y of length n, choose three distinct indices i, j, k
 * whose x-values are pairwise distinct (x[i], x[j], x[k] all different) so as to
 * maximize y[i] + y[j] + y[k]. Return that maximum sum, or -1 if no valid triplet
 * exists (i.e. fewer than three distinct x-values).
 *
 * Input  : vector<int> x, vector<int> y (same length n).
 * Output : int — the maximum achievable y-sum over a distinct-x triplet, else -1.
 *
 * Constraints: 3 <= n <= 1e5, 1 <= x[i], y[i] <= 1e6.
 *
 * Approach: The triplet uses three DIFFERENT x-values, and each x-value can supply only
 *   one index, so for a given x-value only its largest y is ever worth taking. Collapse
 *   the data to best[x] = max y over all indices sharing that x-value. The optimal
 *   triplet then just picks the three x-values with the largest such maxima: those three
 *   maxima come from three distinct x-values (hence three distinct indices with distinct
 *   x), so their sum is both achievable and clearly maximal. If there are fewer than
 *   three distinct x-values, no triplet exists -> return -1. Finding the top three maxima
 *   is a single linear scan keeping the running three largest.
 *
 * Complexity: O(n) time (one pass to build the map, one to take the top three),
 *   O(d) space where d is the number of distinct x-values.
 */

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y) {
        int n = (int)x.size();

        // Keep, per x-value, only the maximum y — the only candidate that value can offer.
        unordered_map<int, int> best;
        for (int i = 0; i < n; ++i) {
            auto it = best.find(x[i]);
            if (it == best.end() || y[i] > it->second)
                best[x[i]] = y[i];
        }

        if (best.size() < 3) return -1;         // need three distinct x-values

        // Track the three largest maxima (m1 >= m2 >= m3). Sentinels sit below any y (y>=1),
        // and with >= 3 distinct values all three slots are guaranteed to be overwritten.
        long long m1 = -1, m2 = -1, m3 = -1;
        for (const auto& [xv, yv] : best) {
            if (yv > m1)      { m3 = m2; m2 = m1; m1 = yv; }   // new overall max, cascade down
            else if (yv > m2) { m3 = m2; m2 = yv; }            // new second best
            else if (yv > m3) { m3 = yv; }                     // new third best
        }
        return (int)(m1 + m2 + m3);             // <= 3e6, safely within int range
    }
};
