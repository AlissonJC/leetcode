/*
 * LeetCode 78 - Subsets
 *
 * Given an array nums of distinct integers, return every possible subset — the power
 * set. The result must contain no duplicate subsets and may be returned in any order.
 *
 * Input  : vector<int>& nums. Output : vector<vector<int>> — all 2^n subsets.
 *
 * Constraints: 1 <= nums.length <= 10; -10 <= nums[i] <= 10; all elements unique.
 *
 * Approach: Backtracking over the indices of nums. The DFS carries a `start` index and
 *   the subset built so far; crucially it records the current subset at EVERY node of
 *   the recursion, because each partial path is itself a valid subset (the empty set is
 *   recorded at the root). From a node it then tries appending each element at index
 *   i >= start, recursing with i+1 so no index is reused and elements are only ever
 *   added in increasing index order — that ordering guarantees each subset is generated
 *   exactly once, with no duplicates. Since the inputs are unique, no extra de-duping is
 *   needed. n <= 10 means at most 2^10 = 1024 subsets, so the full enumeration is cheap.
 *
 * Complexity: O(n * 2^n) time (2^n subsets, each up to length n to copy); O(n) auxiliary
 *   recursion/path depth beyond the output.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        current.reserve(nums.size());
        backtrack(0, nums, current, result);
        return result;
    }

private:
    void backtrack(int start, vector<int>& nums,
                   vector<int>& current, vector<vector<int>>& result) {
        // Every node is a valid subset (the empty set included), so record it here.
        result.push_back(current);
        for (int i = start; i < (int)nums.size(); ++i) {
            current.push_back(nums[i]);
            backtrack(i + 1, nums, current, result);   // only pick later indices -> no repeats
            current.pop_back();                          // undo to try the next element
        }
    }
};
