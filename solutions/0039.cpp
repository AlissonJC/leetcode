/*
 * LeetCode 39 - Combination Sum
 *
 * Given an array of DISTINCT positive integers candidates and a target, return
 * every unique combination of candidates that sums to target. Each candidate may
 * be reused an unlimited number of times; two combinations differ when some value
 * is chosen a different number of times (order does not matter).
 *
 * Input  : vector<int>& candidates, int target. Output : vector<vector<int>> of
 *          all distinct multisets summing to target (any order).
 *
 * Constraints: 1 <= n <= 30; 2 <= candidates[i] <= 40, all distinct; 1 <= target
 *   <= 40. Sums stay tiny (<= 40), so plain int suffices and the search is small.
 *
 * Approach: depth-first backtracking that builds combinations in non-decreasing
 *   order to avoid permutational duplicates. Sort candidates first, then at each
 *   step only consider candidates from the current index onward; recursing on the
 *   SAME index (i, not i+1) models reusing a number any number of times, while
 *   never looking back prevents generating the same multiset in a different order.
 *   Subtract the chosen value from the remaining target and recurse; on reaching
 *   exactly zero, record the path. Because the array is sorted, the first index
 *   whose value exceeds the remaining target lets us break the loop early — no
 *   larger candidate can fit either.
 *
 * Complexity: O(number of nodes in the search tree) time, bounded by the count of
 *   valid combinations times the path length; O(target / min_candidate) recursion
 *   depth and O(1) auxiliary space beyond the output and the current path.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // Sorting enables the "break once candidate > remaining" pruning and keeps
        // every recorded combination in non-decreasing order.
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
            // Path sums exactly to target: it's a valid combination.
            result.push_back(path);
            return;
        }

        for (int i = start; i < (int)candidates.size(); ++i) {
            // Sorted: this candidate (and all after it) overshoot the remainder.
            if (candidates[i] > remaining)
                break;

            // Choose candidates[i]; pass i (not i+1) so it can be reused.
            path.push_back(candidates[i]);
            backtrack(candidates, remaining - candidates[i], i, path, result);
            path.pop_back();                    // undo the choice (backtracking)
        }
    }
};
