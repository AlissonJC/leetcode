/*
 * LeetCode 40 - Combination Sum II
 *
 * Given a collection of candidate numbers that MAY contain duplicates and a
 * target, return every unique combination whose numbers sum to target. Unlike
 * Combination Sum I, each array element may be used at most once, and the result
 * must not contain duplicate combinations even though the input can repeat values.
 *
 * Input  : vector<int>& candidates (with possible repeats), int target.
 * Output : vector<vector<int>> of all distinct combinations summing to target.
 *
 * Constraints: 1 <= n <= 100; 1 <= candidates[i] <= 50; 1 <= target <= 30. Sums
 *   stay tiny, so plain int is fine and the pruned search is small.
 *
 * Approach: backtracking over a sorted array, with two adjustments versus the
 *   "unlimited reuse" version. (1) Each element is used at most once, so recursion
 *   advances to i+1 rather than staying on i. (2) Because equal values now sit
 *   adjacent after sorting, skipping a value that equals its predecessor AT THE
 *   SAME recursion level (i > start && candidates[i] == candidates[i-1]) avoids
 *   producing the same combination twice: the first copy of a duplicate value
 *   already explores every continuation, so starting a sibling branch with an
 *   identical value would only repeat work. Sorting also permits the usual early
 *   break once a candidate exceeds the remaining target.
 *
 * Complexity: O(2^n) combinations in the worst case, but the target bound and the
 *   duplicate/over-target prunes keep it small. Recursion depth O(target);
 *   O(1) auxiliary space beyond the output and the current path.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // Sort so duplicates are adjacent (needed by the same-level skip) and so
        // the "> remaining" early break is valid.
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> path;
        backtrack(candidates, target, 0, path, result);
        return result;
    }

private:
    void backtrack(const vector<int>& candidates, int remaining, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(path);             // path sums exactly to target
            return;
        }

        for (int i = start; i < (int)candidates.size(); ++i) {
            // Same-level duplicate guard: only the first of a run of equal values
            // may begin a branch at this depth; later equals would repeat combos.
            if (i > start && candidates[i] == candidates[i - 1])
                continue;

            // Sorted: this and every later candidate overshoot the remainder.
            if (candidates[i] > remaining)
                break;

            // Use candidates[i] once; advance to i+1 so it cannot be reused.
            path.push_back(candidates[i]);
            backtrack(candidates, remaining - candidates[i], i + 1, path, result);
            path.pop_back();                    // undo the choice (backtracking)
        }
    }
};
