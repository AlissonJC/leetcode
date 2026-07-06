/*
 * LeetCode 1301 - Number of Paths with Max Score
 *
 * A square grid `board` of characters. You start on the bottom-right cell marked
 * 'S' and must reach the top-left cell marked 'E'. Every other cell is either a
 * digit '1'..'9' or an obstacle 'X'. From a cell you may step one square up, left,
 * or up-left (diagonally), never onto an obstacle. Walking onto a digit cell
 * collects that digit's value ('S' and 'E' collect nothing). Return the pair
 * {maximum collectible sum, number of distinct paths achieving that sum modulo
 * 1e9+7}. If no path from S to E exists, return {0, 0}.
 *
 * Input  : vector<string>& board -- board[r][c] in {'S','E','X','1'..'9'};
 *          'S' sits at (n-1, n-1) and 'E' at (0, 0).
 * Output : vector<int> of size 2 -- {maxSum, pathCount % (1e9+7)}.
 *
 * Constraints: 2 <= n == board.length == board[i].length <= 100.
 *
 * Approach: dynamic programming over cells. The three legal moves (up, left,
 *   up-left) all decrease a coordinate, so a path is a monotone walk from S toward
 *   E. Define best[r][c] = maximum sum on any partial path from S to (r,c), and
 *   ways[r][c] = how many such best-sum paths reach (r,c). A move *into* (r,c) can
 *   only have come from (r+1,c), (r,c+1), or (r+1,c+1); each of those has a larger
 *   row or larger column, so filling cells in decreasing (r,c) order guarantees the
 *   three predecessors are already computed. Take the largest predecessor sum, add
 *   this cell's digit value, and sum the way-counts of every predecessor tied for
 *   that largest sum. 'X' cells and cells with no reachable predecessor stay
 *   unreachable (sentinel -1). The answer lives in cell (0,0) = 'E'.
 *
 * Complexity: O(n^2) time and O(n^2) space -- one pass over the grid with O(1) work
 *   (three predecessors) per cell. The max sum is bounded by 9*(2n-1) < 1800 so it
 *   fits an int; the path count is kept modulo 1e9+7 in a 64-bit accumulator.
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1'000'000'007;
        int n = static_cast<int>(board.size());

        // best[r][c] = max sum of a path from S to (r,c); -1 means unreachable.
        // ways[r][c] = count (mod MOD) of such maximum-sum paths reaching (r,c).
        vector<vector<int>> best(n, vector<int>(n, -1));
        vector<vector<long long>> ways(n, vector<long long>(n, 0));

        // The three cells one can step *from* to arrive at the current cell,
        // i.e. the reverse of the up / left / up-left moves.
        const int dr[3] = {1, 0, 1};
        const int dc[3] = {0, 1, 1};

        // Fill in decreasing row then decreasing column so every predecessor
        // (larger row or larger column) is ready before we use it.
        for (int r = n - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if (board[r][c] == 'X') continue;      // obstacle: stays unreachable

                if (r == n - 1 && c == n - 1) {        // 'S': the start, collects 0
                    best[r][c] = 0;
                    ways[r][c] = 1;
                    continue;
                }

                // Combine the three predecessors, keeping the max sum and the
                // total way-count over predecessors tied for that max.
                int bestPred = -1;
                long long total = 0;
                for (int k = 0; k < 3; ++k) {
                    int pr = r + dr[k], pc = c + dc[k];
                    if (pr >= n || pc >= n) continue;  // off the board
                    if (best[pr][pc] == -1) continue;  // predecessor unreachable
                    if (best[pr][pc] > bestPred) {
                        bestPred = best[pr][pc];
                        total = ways[pr][pc];
                    } else if (best[pr][pc] == bestPred) {
                        total = (total + ways[pr][pc]) % MOD;
                    }
                }

                if (bestPred == -1) continue;          // no way in: unreachable

                // 'E' contributes 0; every other reachable cell here is a digit.
                int gain = (board[r][c] == 'E') ? 0 : board[r][c] - '0';
                best[r][c] = bestPred + gain;
                ways[r][c] = total;                    // already reduced mod MOD
            }
        }

        // 'E' is the top-left cell. Unreachable => no path at all.
        if (best[0][0] == -1) return {0, 0};
        return {best[0][0], static_cast<int>(ways[0][0])};
    }
};
