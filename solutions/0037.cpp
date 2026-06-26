/*
 * LeetCode 37 - Sudoku Solver
 *
 * Fill every empty cell ('.') of a 9x9 Sudoku board so that each digit 1-9 occurs
 * exactly once in every row, every column, and every 3x3 sub-box. The board is
 * modified in place. The input is guaranteed to have exactly one solution.
 *
 * Input  : vector<vector<char>>& board, 9x9, each cell a digit '1'-'9' or '.'.
 * Output : void — board is mutated to hold the completed solution.
 *
 * Constraints: board is exactly 9x9; cells are '1'-'9' or '.'; a unique solution
 *   exists. Fixed tiny grid, so backtracking with O(1) constraint checks is fast.
 *
 * Approach: depth-first backtracking with incremental constraint tracking. Keep
 *   three boolean tables — rowUsed[r][d], colUsed[c][d], boxUsed[b][d] — recording
 *   whether digit d already sits in row r, column c, or box b = (r/3)*3 + c/3.
 *   First sweep the board to register all given digits and to collect the list of
 *   empty cells. Then fill the empties one at a time: for the k-th empty cell try
 *   every digit not already used in its row, column, and box; place it (updating
 *   the three tables) and recurse to cell k+1. If the recursion completes the
 *   board, propagate success; otherwise undo the placement and try the next digit.
 *   Because a solution is guaranteed unique, the first time all empties are filled
 *   the board holds the answer.
 *
 * Complexity: worst case exponential in the number of empty cells, but the three
 *   constraint tables prune so aggressively that real 9x9 boards solve in well
 *   under a millisecond. O(1) extra space (fixed 9x9 tables and <=81 empties).
 */

#include <vector>
#include <utility>
#include <cstring>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // Clear state, in case the same object is reused across calls.
        memset(rowUsed, 0, sizeof(rowUsed));
        memset(colUsed, 0, sizeof(colUsed));
        memset(boxUsed, 0, sizeof(boxUsed));
        empties.clear();

        // Register every given digit and gather the blank cells to fill.
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') {
                    empties.emplace_back(r, c);
                } else {
                    int d = board[r][c] - '1';          // '1'..'9' -> 0..8
                    int b = boxOf(r, c);
                    rowUsed[r][d] = colUsed[c][d] = boxUsed[b][d] = true;
                }
            }
        }

        solve(board, 0);                                // fills board in place
    }

private:
    bool rowUsed[9][9];
    bool colUsed[9][9];
    bool boxUsed[9][9];
    vector<pair<int, int>> empties;

    static int boxOf(int r, int c) { return (r / 3) * 3 + (c / 3); }

    // Try to fill empties[k..]; returns true once the whole board is solved.
    bool solve(vector<vector<char>>& board, int k) {
        if (k == (int)empties.size())
            return true;                                // no blanks left: solved

        int r = empties[k].first, c = empties[k].second;
        int b = boxOf(r, c);

        for (int d = 0; d < 9; ++d) {
            // Skip digits that already appear along this cell's row, column, or box.
            if (rowUsed[r][d] || colUsed[c][d] || boxUsed[b][d])
                continue;

            // Tentatively place digit d+1 and mark it used everywhere it matters.
            rowUsed[r][d] = colUsed[c][d] = boxUsed[b][d] = true;
            board[r][c] = char('1' + d);

            if (solve(board, k + 1))
                return true;                            // this choice led to a full solution

            // Dead end: retract the digit and try the next candidate.
            rowUsed[r][d] = colUsed[c][d] = boxUsed[b][d] = false;
            board[r][c] = '.';
        }

        return false;                                   // no digit fits: backtrack
    }
};
