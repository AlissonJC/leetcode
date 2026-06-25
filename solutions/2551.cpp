/*
 * LeetCode 2551 - Put Marbles in Bags
 *
 * Distribute n marbles with weights[] into exactly k contiguous, non-empty bags
 * (if marbles i and j share a bag, every marble between them is in it too). A bag
 * spanning indices i..j costs weights[i] + weights[j], and the score of a
 * distribution is the sum of all bag costs. Return the difference between the
 * maximum and minimum scores achievable over all valid distributions.
 *
 * Input  : vector<int> weights, int k. Output : long long — max score - min score.
 *
 * Constraints: 1 <= k <= weights.length <= 1e5; 1 <= weights[i] <= 1e9. An
 *   adjacent-pair sum reaches 2e9 and the accumulated difference up to ~2e14, so
 *   64-bit integers are required.
 *
 * Approach: forming k bags means cutting the row at k-1 of the n-1 gaps between
 *   adjacent marbles. The very first and very last marble are always the outer
 *   endpoints of the first and last bag, so weights[0] + weights[n-1] is added in
 *   every distribution — a constant. A cut placed between positions p and p+1
 *   turns weights[p] into a bag's right end and weights[p+1] into the next bag's
 *   left end, contributing weights[p] + weights[p+1] to the score. So the only
 *   choice that matters is which k-1 of the n-1 adjacent-pair sums to include.
 *   The maximum score takes the k-1 largest pair sums, the minimum takes the k-1
 *   smallest, and the constant endpoints cancel when we subtract. Sort the pair
 *   sums and return (sum of the largest k-1) - (sum of the smallest k-1).
 *
 * Complexity: O(n log n) time (sorting n-1 pair sums) and O(n) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = (int)weights.size();
        if (k == 1) return 0;          // one bag: a single fixed score, difference 0

        // pair[p] = weights[p] + weights[p+1] for each gap p in [0, n-2].
        vector<long long> pairs;
        pairs.reserve(n - 1);
        for (int p = 0; p + 1 < n; ++p)
            pairs.push_back((long long)weights[p] + weights[p + 1]);

        sort(pairs.begin(), pairs.end());

        // Choosing k-1 cuts: largest k-1 maximize the score, smallest k-1 minimize
        // it; the always-present endpoint weights cancel in the difference.
        long long diff = 0;
        int cuts = k - 1;
        int m = (int)pairs.size();
        for (int i = 0; i < cuts; ++i) {
            diff += pairs[m - 1 - i];  // i-th largest pair sum
            diff -= pairs[i];          // i-th smallest pair sum
        }
        return diff;
    }
};
