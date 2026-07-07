/*
 * LeetCode 73 - Set Matrix Zeroes
 *
 * Given an m x n integer matrix, if any element is 0, set that element's entire row
 * and entire column to 0. The transformation must be done in place.
 *
 * Input  : vector<vector<int>>& matrix (modified in place). Output : none.
 *
 * Constraints: 1 <= m, n <= 200; -2^31 <= matrix[i][j] <= 2^31 - 1. The follow-up
 *   asks for a constant-space solution (no O(mn) or O(m+n) auxiliary storage).
 *
 * Approach: Use the matrix's own first row and first column as the bookkeeping for
 *   which rows and columns must be zeroed, achieving O(1) extra space. matrix[i][0]
 *   records "row i must be zeroed" and matrix[0][j] records "column j must be zeroed".
 *   The single cell matrix[0][0] would have to mean both "row 0" and "column 0", so
 *   column 0 is tracked in a separate boolean firstCol and matrix[0][0] is left to
 *   mean "row 0". First pass: for every original zero at (i, j) with j >= 1, stamp
 *   matrix[i][0] = 0 and matrix[0][j] = 0; a zero in column 0 just sets firstCol.
 *   Second pass: walk the rows from the bottom up so that row 0 (which holds the
 *   column markers) is applied last, after every other row has read those markers;
 *   within a row, zero cells whose row-marker or column-marker is 0, then finally
 *   zero the row's column-0 cell if firstCol is set (done after reading the marker).
 *
 * Complexity: O(m * n) time, O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        bool firstCol = false;   // does column 0 contain an original zero?

        // Pass 1 — record which rows/columns need zeroing into the borders.
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) firstCol = true;   // column-0 zeros tracked separately
            for (int j = 1; j < n; ++j) {             // j starts at 1: never overwrite col-0 markers
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;   // mark row i
                    matrix[0][j] = 0;   // mark column j
                }
            }
        }

        // Pass 2 — apply the markers from bottom-right upward. Going bottom-up keeps
        // row 0's column-markers intact until every lower row has consumed them.
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 1; --j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
            }
            // Zero column 0 last for this row, after its row-marker matrix[i][0] was read.
            if (firstCol) matrix[i][0] = 0;
        }
    }
};
