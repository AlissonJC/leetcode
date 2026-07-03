/*
 * LeetCode 51 - N-Queens
 *
 * Place n queens on an n x n chessboard so that no two queens attack each
 * other - no two may share a row, a column, or a diagonal. Return all distinct
 * board configurations that achieve this. Each board is given as n strings of
 * length n, where 'Q' marks a queen and '.' marks an empty square.
 *
 * Input  : int n - the board size and the number of queens to place.
 * Output : vector<vector<string>> - every valid arrangement, each an n-string
 *          picture of the board.
 *
 * Constraints: 1 <= n <= 9.
 *
 * Approach: backtracking one row at a time. Since every row must hold exactly
 *   one queen, recurse row by row and, within a row, try each column. A square
 *   (row, col) is safe unless its column or one of its two diagonals is already
 *   taken, so keep three boolean marker sets for O(1) conflict tests: col[c],
 *   the "\" diagonal keyed by row - col, and the "/" diagonal keyed by
 *   row + col. Placing a queen sets its three markers and recording its column;
 *   undoing a placement clears them. When the recursion passes the last row,
 *   every row has a conflict-free queen, so render the recorded columns into a
 *   board and save it. With n <= 9 the pruned search is tiny (at most 352
 *   solutions, for n = 9).
 *
 * Complexity: worst-case exponential in n from the branching search, but the
 *   diagonal/column pruning and n <= 9 keep it effectively constant; O(n)
 *   recursion depth plus O(n) space for the markers and the column record
 *   (output not counted).
 */

#include <vector>
#include <string>
#include <utility>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<int> pos(n, -1);          // pos[r] = column of the queen placed in row r

        // One marker per column and per diagonal. A "\" diagonal has constant
        // row - col in [-(n-1), n-1], shifted by (n-1) into [0, 2n-2]; a "/"
        // diagonal has constant row + col already in [0, 2n-2].
        vector<bool> col(n, false), diagMain(2 * n - 1, false), diagAnti(2 * n - 1, false);

        backtrack(0, n, pos, col, diagMain, diagAnti, result);
        return result;
    }

private:
    void backtrack(int row, int n, vector<int>& pos,
                   vector<bool>& col, vector<bool>& diagMain, vector<bool>& diagAnti,
                   vector<vector<string>>& result) {
        // All n rows filled -> the recorded columns describe one valid board.
        if (row == n) {
            vector<string> board(n, string(n, '.'));
            for (int r = 0; r < n; ++r) board[r][pos[r]] = 'Q';
            result.push_back(move(board));
            return;
        }

        for (int c = 0; c < n; ++c) {
            int m = row - c + (n - 1);   // "\" diagonal index (shifted non-negative)
            int a = row + c;             // "/" diagonal index

            // Skip squares attacked by a queen already placed in an earlier row.
            if (col[c] || diagMain[m] || diagAnti[a]) continue;

            // choose: occupy the column and both diagonals, record the position
            col[c] = diagMain[m] = diagAnti[a] = true;
            pos[row] = c;

            // explore the next row
            backtrack(row + 1, n, pos, col, diagMain, diagAnti, result);

            // un-choose: release the markers so the next column starts clean
            col[c] = diagMain[m] = diagAnti[a] = false;
        }
    }
};
