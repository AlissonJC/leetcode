/*
 * LeetCode 77 - Combinations
 *
 * Given two integers n and k, return every possible combination of k distinct numbers
 * chosen from the range [1, n]. Combinations are unordered ([1,2] equals [2,1]); the
 * list of combinations may be returned in any order.
 *
 * Input  : int n, int k. Output : vector<vector<int>> — all k-subsets of {1..n}.
 *
 * Constraints: 1 <= k <= n <= 20.
 *
 * Approach: Backtracking that builds each combination in strictly increasing order, so
 *   every k-subset is generated exactly once (no permutations, no duplicates). A DFS
 *   carries the next allowed value `start`; at each level it appends a candidate i,
 *   recurses from i+1, then pops it to try the next candidate. Recording happens when
 *   the current path reaches length k. A pruning bound keeps it efficient: if `need`
 *   more numbers are required, any start i must leave at least `need` values in [i, n],
 *   so i only ranges up to n - need + 1 — branches that cannot be completed are never
 *   explored.
 *
 * Complexity: O(k * C(n, k)) time to emit all C(n, k) combinations of length k; O(k)
 *   auxiliary stack/path depth beyond the output itself.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;
        current.reserve(k);
        backtrack(1, n, k, current, result);
        return result;
    }

private:
    void backtrack(int start, int n, int k,
                   vector<int>& current, vector<vector<int>>& result) {
        if ((int)current.size() == k) {   // a full combination is assembled
            result.push_back(current);
            return;
        }
        int need = k - (int)current.size();   // how many numbers are still required
        // Stop at n - need + 1: any larger start leaves fewer than `need` values in [i, n].
        for (int i = start; i <= n - need + 1; ++i) {
            current.push_back(i);
            backtrack(i + 1, n, k, current, result);   // next pick must exceed i
            current.pop_back();                          // undo to explore the next candidate
        }
    }
};
