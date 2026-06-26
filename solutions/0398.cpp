/*
 * LeetCode 398 - Random Pick Index
 *
 * Given an integer array nums that may contain duplicates, support pick(target):
 * return a uniformly random index i with nums[i] == target. target is guaranteed
 * to occur in nums, and when it occurs several times every matching index must be
 * equally likely.
 *
 * Interface:
 *   Solution(vector<int>& nums) - store/preprocess the array.
 *   pick(target)                - return a random index i where nums[i] == target.
 *
 * Constraints: 1 <= n <= 2*10^4; -2^31 <= nums[i] <= 2^31 - 1 (so keys need a full
 *   int); target always exists; up to 10^4 calls to pick.
 *
 * Approach: bucket indices by value once in the constructor — a hash map from each
 *   value to the list of positions where it appears. Then pick(target) is a single
 *   uniform draw over that value's index list, so every matching index is returned
 *   with probability 1/(count of target). This trades O(n) memory for O(1) work per
 *   pick, which matters because with up to 10^4 picks over a 2*10^4 array the
 *   alternative reservoir-sampling method (rescanning the whole array each call,
 *   keeping the i-th match with probability 1/i) would do up to ~2*10^8 RNG draws
 *   in the all-duplicates worst case. Reservoir sampling is the O(1)-space option;
 *   here the bucket map is the faster, TLE-safe choice.
 *
 * Complexity: constructor O(n) time and O(n) space; each pick() O(1) time.
 */

#include <vector>
#include <unordered_map>
#include <random>
using namespace std;

class Solution {
public:
    Solution(vector<int>& nums) : gen(random_device{}()) {
        // Record every index under its value so a pick never rescans the array.
        for (int i = 0; i < (int)nums.size(); ++i)
            buckets[nums[i]].push_back(i);
    }

    int pick(int target) {
        // target is guaranteed present, so .at() never throws (and, unlike [],
        // it won't silently insert an empty bucket on a stray lookup).
        const vector<int>& idx = buckets.at(target);
        // Uniform over the matching positions -> each index equally likely.
        int r = uniform_int_distribution<int>(0, (int)idx.size() - 1)(gen);
        return idx[r];
    }

private:
    unordered_map<int, vector<int>> buckets;  // value -> indices holding it
    mt19937 gen;                              // pseudo-random engine, seeded once
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
