/*
 * LeetCode 384 - Shuffle an Array
 *
 * Design a class that can randomly shuffle an array so that every one of the n!
 * permutations is equally likely, and can also restore the original ordering on demand.
 *
 * Input  : a sequence of Solution(nums), reset(), shuffle() calls.
 * Output : reset() returns the original array; shuffle() returns a uniformly random
 *          permutation of it.
 *
 * Constraints: 1 <= nums.length <= 50; -1e6 <= nums[i] <= 1e6; elements are unique;
 *   up to 1e4 calls to reset/shuffle.
 *
 * Approach: keep an untouched copy of the input for reset, and a working copy to shuffle.
 *   Shuffle with the Fisher-Yates (Durstenfeld) algorithm: walk i from the last index down
 *   to 1 and swap position i with a uniformly random position j in [0, i]. The invariant is
 *   that after handling index i, the suffix i..n-1 holds a uniformly random selection in
 *   random order, so when the loop finishes every permutation occurs with probability
 *   exactly 1/n!. Drawing j from the full prefix [0, i] (including i itself) is what makes
 *   it unbiased — restricting to [0, i-1] would skew the distribution.
 *
 * Complexity: shuffle() and reset() are O(n); O(n) space for the two copies.
 */

#include <vector>
#include <random>
using namespace std;

class Solution {
    vector<int> original;   // pristine copy, used by reset()
    vector<int> current;    // working copy that shuffle() permutes in place
    mt19937 rng;            // random engine, seeded once

public:
    Solution(vector<int>& nums)
        : original(nums), current(nums), rng(random_device{}()) {}

    vector<int> reset() {
        current = original;     // restore the starting configuration
        return current;
    }

    vector<int> shuffle() {
        // Fisher-Yates: fix each position from the end by swapping in a random earlier
        // (or equal) element that has not yet been locked into place.
        for (int i = (int)current.size() - 1; i > 0; --i) {
            uniform_int_distribution<int> dist(0, i);   // inclusive range [0, i]
            int j = dist(rng);
            swap(current[i], current[j]);
        }
        return current;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
