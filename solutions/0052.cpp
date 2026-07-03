/*
 * LeetCode 52 - N-Queens II
 *
 * Count the number of distinct ways to place n queens on an n x n chessboard
 * so that no two queens attack each other - no two share a row, a column, or a
 * diagonal. Only the count of valid arrangements is required, not the boards.
 *
 * Input  : int n - the board size and the number of queens to place.
 * Output : int - how many non-attacking placements exist.
 *
 * Constraints: 1 <= n <= 9.
 *
 * Approach: the same row-by-row backtracking as listing the boards, but here we
 *   only tally completed placements, which lets us track conflicts with plain
 *   integer bitmasks instead of boolean arrays. Three masks over the n columns
 *   record what the queens above the current row already attack: `cols` for
 *   occupied columns, `diagL` for one diagonal direction, `diagR` for the other.
 *   The squares still open in this row are exactly the zero bits of
 *   (cols | diagL | diagR) inside the n-bit board, extracted one at a time by
 *   isolating the lowest set bit (p = avail & -avail). Moving down to the next
 *   row shifts the diagonal masks by one - left for diagL, right for diagR -
 *   because a diagonal threat advances one column per row; that single shift is
 *   what keeps the diagonal bookkeeping O(1). A branch that manages to fill all
 *   n columns (cols == full) is one solution. Bitmask operations plus n <= 9
 *   make the whole search instantaneous.
 *
 * Complexity: worst-case exponential in n from the branching, but heavily
 *   pruned and trivial for n <= 9; O(n) recursion depth and O(1) extra space -
 *   the masks are just a few integers.
 */

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        full = (1 << n) - 1;         // n low bits set: the whole row of columns
        return count(0, 0, 0);
    }

private:
    int full;   // bitmask with the n valid column bits set

    // cols / diagL / diagR encode the columns and two diagonals attacked from
    // the rows already filled above. Returns the number of ways to complete the
    // board from here.
    int count(int cols, int diagL, int diagR) {
        // Every column filled without conflict -> a full valid arrangement.
        if (cols == full) return 1;

        // Open squares in this row: bits free of column and both diagonal hits.
        int avail = full & ~(cols | diagL | diagR);

        int total = 0;
        while (avail) {
            int p = avail & (-avail);   // isolate the lowest available square
            avail -= p;                 // consume it from this row's options

            // Place a queen on p, then descend: the diagonal masks shift by one
            // column since diagonal attacks move one step per row downward.
            total += count(cols | p, (diagL | p) << 1, (diagR | p) >> 1);
        }
        return total;
    }
};
