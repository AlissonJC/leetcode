/*
 * LeetCode 36 - Valid Sudoku
 *
 * Decide whether a partially filled 9x9 Sudoku board is valid. Validity requires
 * that no digit 1-9 repeats within any single row, any single column, or any of
 * the nine 3x3 sub-boxes. Empty cells (marked '.') impose no constraint, and a
 * board only needs to be consistent — it need not be solvable.
 *
 * Input  : vector<vector<char>>& board, 9x9, each cell a digit '1'-'9' or '.'.
 * Output : bool — true if the filled cells violate none of the three rules.
 *
 * Constraints: board is exactly 9x9; each cell is '1'-'9' or '.'. Fixed tiny size,
 *   so a single linear pass is trivially fast.
 *
 * Approach: scan all 81 cells once, maintaining three sets of "seen" flags — one
 *   per row, one per column, one per 3x3 box. For a filled cell at (r, c) holding
 *   digit d, the owning box is index (r/3)*3 + (c/3) (0..8). If d has already been
 *   recorded for that row, column, or box, a rule is broken and the board is
 *   invalid; otherwise mark d as seen in all three and continue. Surviving every
 *   cell means no duplicates exist anywhere, so the board is valid.
 *
 * Complexity: O(81) = O(1) time over the fixed board; O(1) space (three 9x9 flag
 *   tables).
 */

#include <vector>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // seenInRow[r][d] = digit d (0..8) already appears in row r; likewise for
        // columns and 3x3 boxes. Fixed-size, so they cost constant space.
        bool seenInRow[9][9] = {false};
        bool seenInCol[9][9] = {false};
        bool seenInBox[9][9] = {false};

        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                char ch = board[r][c];
                if (ch == '.')
                    continue;                       // empty cell: nothing to check

                int d = ch - '1';                   // map '1'..'9' -> 0..8
                int box = (r / 3) * 3 + (c / 3);     // which 3x3 sub-box owns (r,c)

                // A repeat in this cell's row, column, or box breaks Sudoku validity.
                if (seenInRow[r][d] || seenInCol[c][d] || seenInBox[box][d])
                    return false;

                // Record the digit as present along all three lines.
                seenInRow[r][d] = true;
                seenInCol[c][d] = true;
                seenInBox[box][d] = true;
            }
        }

        return true;                                // no conflicts anywhere
    }
};
