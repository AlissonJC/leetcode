/*
 * LeetCode 528 - Random Pick with Weight
 *
 * Given positive weights w[0..n-1], implement pickIndex() so that index i is returned with
 * probability w[i] / sum(w).
 *
 * Input  : a sequence of Solution(w), pickIndex() calls.
 * Output : pickIndex() returns an index in [0, n-1] with the weighted probability above.
 *
 * Constraints: 1 <= n <= 1e4; 1 <= w[i] <= 1e5; up to 1e4 pickIndex calls.
 *
 * Approach: lay the weights end to end on a number line so index i owns the half-open
 *   segment (prefix[i-1], prefix[i]] of length w[i], where prefix is the running sum of
 *   weights. Since weights are positive, prefix is strictly increasing. To sample, draw a
 *   uniform integer target in [1, total] and return the index of the segment it lands in,
 *   found as the first prefix >= target via binary search (lower_bound). Exactly w[i] of
 *   the total targets map to index i, so the probability is w[i] / total, as required.
 *   Using an integer target keeps the sampling exact — no floating-point rounding.
 *
 * Overflow note: total = sum(w) can reach 1e4 * 1e5 = 1e9, which fits in 32 bits but is
 *   close to the edge; the prefix sums and total are kept in long long to be safe.
 *
 * Complexity: O(n) construction; O(log n) per pickIndex; O(n) space.
 */

#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Solution {
    vector<long long> prefix;   // prefix[i] = w[0] + ... + w[i], strictly increasing
    long long total;            // sum of all weights
    mt19937 rng;                // random engine, seeded once

public:
    Solution(vector<int>& w) : rng(random_device{}()) {
        prefix.reserve(w.size());
        long long running = 0;
        for (int weight : w) {
            running += weight;
            prefix.push_back(running);
        }
        total = running;
    }

    int pickIndex() {
        // Draw a target in [1, total]; index i wins iff prefix[i-1] < target <= prefix[i].
        uniform_int_distribution<long long> dist(1, total);
        long long target = dist(rng);
        // The first prefix >= target identifies the owning segment.
        int idx = (int)(lower_bound(prefix.begin(), prefix.end(), target) - prefix.begin());
        return idx;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
