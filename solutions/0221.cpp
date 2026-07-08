/*
 * LeetCode 221 - Maximal Square
 *
 * Given an m x n binary matrix of '0'/'1' characters, return the area of the largest
 * square that contains only '1's.
 *
 * Input  : vector<vector<char>> matrix, each entry '0' or '1'.
 * Output : int — the area (side^2) of the largest all-ones square.
 *
 * Constraints: 1 <= m, n <= 300, matrix[i][j] in {'0','1'}.
 *
 * Approach: Dynamic programming on square sides. Let side(i,j) be the edge length of the
 *   largest all-ones square whose BOTTOM-RIGHT corner is cell (i,j). A square of side s
 *   ending at (i,j) exists iff the cell is '1' and squares of side s-1 end at its top, left,
 *   and top-left neighbors, so side(i,j) = 1 + min(side(i-1,j), side(i,j-1), side(i-1,j-1))
 *   when matrix[i][j]=='1', else 0. The answer is (max side)^2. Only the previous row and
 *   one diagonal value are needed, so a single rolling 1D array (columns 1..n, index 0 as a
 *   zero left-border) plus a 'diag' variable holding side(i-1,j-1) suffices.
 *
 * Overflow: side <= min(m,n) <= 300, area <= 90000 — all within int.
 *
 * Complexity: O(m * n) time, O(n) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = (int)matrix.size();
        if (m == 0) return 0;
        int n = (int)matrix[0].size();

        vector<int> dp(n + 1, 0);           // dp[j] = side of square ending at (current row, col j-1)
        int best = 0;

        for (int i = 0; i < m; ++i) {
            int diag = 0;                   // side(i-1, j-1); the left border makes it 0 at row start
            for (int j = 1; j <= n; ++j) {
                int topSaved = dp[j];       // dp[j] still holds side(i-1, j) — becomes next diag
                if (matrix[i][j - 1] == '1') {
                    // dp[j-1] is the already-updated side(i, j-1) = left neighbor.
                    dp[j] = 1 + min({dp[j - 1], dp[j], diag});   // left, top, top-left
                    best = max(best, dp[j]);
                } else {
                    dp[j] = 0;              // a '0' cell can end no square
                }
                diag = topSaved;            // side(i-1, j) is the diagonal for the next column
            }
        }
        return best * best;                 // area, not side
    }
};
