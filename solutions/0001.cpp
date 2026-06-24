/*
 * LeetCode 1 - Two Sum
 *
 * Given an array of integers nums and an integer target, return the indices of
 * the two numbers that add up to target. Exactly one solution exists and the
 * same element may not be used twice; the pair may be returned in any order.
 *
 * Input  : vector<int> nums, int target (function arguments, no stdin/stdout).
 * Output : vector<int> with the two indices.
 *
 * Constraints: 2 <= nums.length <= 1e4, -1e9 <= nums[i], target <= 1e9.
 *
 * Approach: scan once, keeping a hash map from each seen value to its index.
 *   For the current element nums[i], its partner must equal target - nums[i];
 *   if that complement was already seen, the pair is found. This answers the
 *   follow-up by running in O(n) instead of the O(n^2) brute force.
 *
 * Complexity: O(n) time, O(n) space (the hash map of seen values).
 */

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;            // value -> index already visited
        for (int i = 0; i < (int)nums.size(); ++i) {
            // |target - nums[i]| <= 2e9 < 2^31, so this stays within int range.
            int need = target - nums[i];
            auto it = seen.find(need);
            if (it != seen.end()) return {it->second, i};  // earlier index first
            seen[nums[i]] = i;                   // record current value for later
        }
        return {};                               // unreachable: a solution is guaranteed
    }
};
