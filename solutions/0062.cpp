/*
 * LeetCode 62 - Unique Paths
 *
 * A robot sits on the top-left cell of an m x n grid and wants to reach the
 * bottom-right cell. It may move only one step right or one step down at a time.
 * Count how many distinct paths lead from the start to the destination.
 *
 * Input  : int m (number of rows), int n (number of columns).
 * Output : int - the number of distinct down/right paths.
 *
 * Constraints: 1 <= m, n <= 100. The test data guarantees the answer fits in a
 *   signed 32-bit integer (at most 2 * 10^9).
 *
 * Approach: dynamic programming over the grid. The only moves that land on a
 *   cell come from the cell directly above or directly to its left, so the count
 *   of paths to (i, j) equals paths to (i-1, j) plus paths to (i, j-1). Every
 *   cell in the top row and left column has exactly one path (a straight line),
 *   which seeds the recurrence. Sweeping row by row, a single rolling array of
 *   length n suffices: when processing a row, dp[j] += dp[j-1] combines "from
 *   above" (dp[j]'s value left over from the previous row) with "from the left"
 *   (dp[j-1], already updated for this row). After the last row, dp[n-1] is the
 *   answer. (Equivalently it is the binomial C(m+n-2, m-1): of the m+n-2 total
 *   moves, choose which m-1 go down.)
 *
 * Complexity: O(m * n) time - one update per cell; O(n) space for the rolling
 *   row. Every cell count is <= the final answer <= 2 * 10^9 < 2^31, so int
 *   holds all intermediate values and no addition overflows.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // Top row: exactly one way to reach each cell (keep moving right).
        vector<int> dp(n, 1);

        // Fill each subsequent row. dp[0] stays 1 (left column: keep moving down).
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[j] += dp[j - 1];   // paths from above (old dp[j]) + from left (dp[j-1])

        return dp[n - 1];
    }
};
