/*
 * LeetCode 47 - Permutations II
 *
 * Given a collection of numbers nums that may contain duplicates, return all of
 * its distinct permutations, in any order. With repeated values the naive "all
 * n! orderings" approach produces the same permutation many times, so the
 * challenge is to emit each unique arrangement exactly once.
 *
 * Input  : vector<int>& nums. Output : vector<vector<int>> of unique permutations.
 *
 * Constraints: 1 <= nums.length <= 8; -10 <= nums[i] <= 10. With n <= 8 there are
 *   at most 8! = 40320 orderings, so straightforward backtracking is plenty fast;
 *   the only real work is suppressing duplicates.
 *
 * Approach: sort nums first so equal values sit next to each other, then build
 *   permutations by backtracking with a used[] flag per index. The duplicate
 *   guard is the whole trick: among a group of equal values we force them to be
 *   placed in left-to-right index order. Concretely, before using index i we skip
 *   it when nums[i] == nums[i-1] and the identical neighbour i-1 has NOT been used
 *   in the current path — using i ahead of its equal predecessor would just
 *   re-create a permutation already generated when the roles were reversed.
 *   Sorting is what makes "equal neighbour" mean "adjacent index", enabling this.
 *
 * Complexity: O(n * n!) time worst case — up to n! permutations, each costing
 *   O(n) to assemble and copy into the result. O(n) extra space for the recursion
 *   stack, the used[] array, and the current path (output not counted).
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // Sort so identical values are adjacent; this is what the duplicate guard
        // below relies on (equal values => consecutive indices).
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> path;               // permutation being built
        vector<bool> used(nums.size(), false);
        backtrack(nums, used, path, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, vector<bool>& used,
                   vector<int>& path, vector<vector<int>>& result) {
        // A full-length path is one complete permutation.
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < (int)nums.size(); ++i) {
            if (used[i])
                continue;

            // Duplicate guard: within a run of equal values, only place one when
            // its identical left neighbour is already in the path. If that neighbour
            // is unused, placing nums[i] now would duplicate a permutation produced
            // by the branch that used the neighbour first.
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
                continue;

            // Choose nums[i], recurse, then undo the choice (standard backtracking).
            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, used, path, result);
            path.pop_back();
            used[i] = false;
        }
    }
};
