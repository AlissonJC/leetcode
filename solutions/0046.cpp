/*
 * LeetCode 46 - Permutations
 *
 * Given an array nums of distinct integers, return all possible permutations
 * of its elements. The permutations may be returned in any order.
 *
 * Input  : vector<int> nums - distinct integers.
 * Output : vector<vector<int>> - every ordering of nums, all n! of them.
 *
 * Constraints: 1 <= n == nums.length <= 6; -10 <= nums[i] <= 10; all integers
 *   in nums are unique.
 *
 * Approach: depth-first backtracking that fills the permutation one slot at a
 *   time. A boolean used[] marks which elements are already placed; at each
 *   level try every not-yet-used element as the next value, recurse, then undo
 *   the choice (the classic choose / explore / un-choose pattern). When the
 *   partial arrangement reaches length n it is a finished permutation and gets
 *   recorded. Because every element is distinct there are no duplicate branches
 *   to prune, so the search visits exactly n! leaves - at most 720 for n = 6,
 *   trivially within limits.
 *
 * Complexity: O(n! * n) time - n! permutations, each copied into the output in
 *   O(n); O(n) auxiliary space for the recursion stack, the used[] flags, and
 *   the current path (the output itself is not counted).
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;                       // permutation being built
        vector<bool> used(nums.size(), false);  // used[i] == is nums[i] already placed?
        backtrack(nums, used, path, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, vector<bool>& used,
                   vector<int>& path, vector<vector<int>>& result) {
        // A full-length path is one complete permutation - record it.
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        // Choose the next slot's value among the elements not yet used.
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (used[i]) continue;   // each element appears exactly once per permutation

            // choose
            used[i] = true;
            path.push_back(nums[i]);

            // explore the rest of the arrangement
            backtrack(nums, used, path, result);

            // un-choose: revert state so the next candidate starts clean
            path.pop_back();
            used[i] = false;
        }
    }
};
