/*
 * LeetCode 764 - Largest Plus Sign
 *
 * You are given an integer n and an n x n grid that starts all 1's, except the cells listed
 * in mines (each [x, y]) which are 0. An axis-aligned plus sign of order k has a center cell
 * of 1 plus four arms of length k-1 (up, down, left, right), all cells being 1. Return the
 * order of the largest such plus sign, or 0 if none exists.
 *
 * Input  : int n, vector<vector<int>> mines (zero cells, all pairs distinct).
 * Output : int — the largest plus-sign order.
 *
 * Constraints: 1 <= n <= 500, 1 <= mines.length <= 5000, 0 <= xi, yi < n.
 *
 * Approach: The order of the plus centered at (r,c) is the minimum, over the four
 *   directions, of how many consecutive 1's run from (r,c) outward including (r,c) itself:
 *   each such count is exactly one arm reach plus the center, and the plus is limited by its
 *   shortest arm. Compute those four directional run-lengths with four linear sweeps of the
 *   grid — left-to-right, right-to-left, top-to-bottom, bottom-to-top — where a running
 *   counter increments on a 1 and resets to 0 on a mine. Keep dp[r][c] as the running MIN of
 *   the four counts (start it at n, an upper bound); a mine cell naturally becomes 0. The
 *   answer is the maximum dp value.
 *
 * Complexity: O(n^2) time (four sweeps), O(n^2) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        // Mark mine cells; every other cell is a 1.
        vector<vector<char>> mine(n, vector<char>(n, 0));
        for (const auto& m : mines) mine[m[0]][m[1]] = 1;

        // dp[r][c] will end as min over four directions of the consecutive-1 count; n bounds it.
        vector<vector<int>> dp(n, vector<int>(n, n));

        for (int i = 0; i < n; ++i) {
            // Left-to-right and right-to-left along row i.
            int cnt = 0;
            for (int j = 0; j < n; ++j) { cnt = mine[i][j] ? 0 : cnt + 1; dp[i][j] = min(dp[i][j], cnt); }
            cnt = 0;
            for (int j = n - 1; j >= 0; --j) { cnt = mine[i][j] ? 0 : cnt + 1; dp[i][j] = min(dp[i][j], cnt); }

            // Top-to-bottom and bottom-to-top down column i.
            cnt = 0;
            for (int j = 0; j < n; ++j) { cnt = mine[j][i] ? 0 : cnt + 1; dp[j][i] = min(dp[j][i], cnt); }
            cnt = 0;
            for (int j = n - 1; j >= 0; --j) { cnt = mine[j][i] ? 0 : cnt + 1; dp[j][i] = min(dp[j][i], cnt); }
        }

        int best = 0;
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                best = max(best, dp[r][c]);   // largest achievable plus order
        return best;
    }
};
