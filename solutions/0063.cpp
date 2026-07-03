/*
 * LeetCode 63 - Unique Paths II
 *
 * A robot starts at the top-left of an m x n grid and wants to reach the
 * bottom-right, moving only right or down. Some cells contain an obstacle
 * (marked 1) and cannot be stepped on; free cells are marked 0. Count the
 * number of distinct obstacle-free paths from start to finish.
 *
 * Input  : vector<vector<int>> obstacleGrid - 0 for a free cell, 1 for an
 *          obstacle.
 * Output : int - the number of valid down/right paths.
 *
 * Constraints: 1 <= m, n <= 100; each cell is 0 or 1. The test data guarantees
 *   the answer fits in a signed 32-bit integer.
 *
 * Approach: the same additive grid DP as the obstacle-free Unique Paths, with a
 *   single rule change - an obstacle cell can host no path, so its count is
 *   forced to 0 no matter what its neighbors hold. A free cell still sums the
 *   paths arriving from directly above and from directly to the left. A rolling
 *   1D array of length n carries the previous row into the current one: at a
 *   free cell dp[j] += dp[j-1] adds "from the left" (dp[j-1], already this row)
 *   to "from above" (dp[j], left over from the previous row); at an obstacle
 *   dp[j] = 0. Seeding dp[0] = 1 makes the start cell count as one path - and if
 *   the start itself is an obstacle, the same zeroing rule cancels it on the
 *   first visit. After the last row, dp[n-1] is the answer.
 *
 * Complexity: O(m * n) time - one update per cell; O(n) space for the rolling
 *   row. Counts accumulate in 64-bit: with obstacles an interior cell's count
 *   is not bounded by the final answer, so long long keeps the DP safe well
 *   beyond the guaranteed 32-bit result.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = (int)obstacleGrid.size(), n = (int)obstacleGrid[0].size();

        // dp[j] = number of paths to the current row's column j.
        vector<long long> dp(n, 0);
        dp[0] = 1;   // one way "into" the start; cancelled below if it is blocked

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;                 // obstacle: no path can occupy this cell
                } else if (j > 0) {
                    dp[j] += dp[j - 1];        // free: from above (old dp[j]) + from left (dp[j-1])
                }
                // j == 0 free cell: dp[0] carries over unchanged (only "from above").
            }
        }

        return (int)dp[n - 1];
    }
};
