/*
 * LeetCode 64 - Minimum Path Sum
 *
 * Given an m x n grid of non-negative numbers, find a path from the top-left cell to
 * the bottom-right cell that minimizes the sum of the numbers visited, where each move
 * goes only one step right or one step down. Return that minimum sum.
 *
 * Input  : vector<vector<int>>& grid, sized m x n with 0 <= grid[i][j] <= 200.
 * Output : int -- the minimum achievable path sum from (0,0) to (m-1,n-1).
 *
 * Constraints: 1 <= m, n <= 200; 0 <= grid[i][j] <= 200.
 *
 * Approach: dynamic programming over cells. Let best(i,j) be the minimum sum of any
 *   right/down path from (0,0) to (i,j). A cell is reached only from directly above or
 *   directly left, so best(i,j) = grid[i][j] + min(best(i-1,j), best(i,j-1)); the top
 *   row and left column are pure prefix sums since they have a single incoming
 *   direction. Compute row by row, keeping just one rolling array dp of length n: when
 *   processing row i, dp[j] already holds best(i-1,j) (the value from above) and dp[j-1]
 *   holds best(i,j-1) (the value from the left just computed), so each update needs only
 *   those two. The answer is dp[n-1] after the last row.
 *
 * Complexity: O(m * n) time (each cell handled once) and O(n) space for the rolling
 *   row. The largest path sum is about (m+n-1) * 200 <= 79800, well within int range.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());

        // dp[j] = min path sum to the current row's cell (i, j).
        vector<int> dp(n);

        // Row 0: only reachable by moving right, so it is a prefix sum.
        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        // Rows 1..m-1: combine the value from above (old dp[j]) and from the
        // left (freshly updated dp[j-1]).
        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0];                         // leftmost column: only from above
            for (int j = 1; j < n; ++j) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
            }
        }

        return dp[n - 1];                                // best sum to reach bottom-right
    }
};
