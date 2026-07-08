/*
 * LeetCode 304 - Range Sum Query 2D - Immutable
 *
 * Design a class over a fixed 2D integer matrix that answers many rectangle-sum queries in
 * O(1). sumRegion(row1, col1, row2, col2) returns the sum of all elements inside the
 * rectangle with upper-left (row1, col1) and lower-right (row2, col2), inclusive.
 *
 *   NumMatrix(vector<vector<int>> matrix) : precompute helpers.
 *   int sumRegion(int row1, int col1, int row2, int col2) : rectangle sum.
 *
 * Input/Output: method calls (no stdin/stdout); sumRegion returns an int.
 *
 * Constraints: 1 <= m, n <= 200, -1e4 <= matrix[i][j] <= 1e4, valid corners, up to 1e4 calls.
 *
 * Approach: 2D prefix sums. Precompute pre[i][j] = sum of the sub-matrix matrix[0..i-1][0..j-1],
 *   with an all-zero first row and column so boundaries need no special cases. Each cell fills
 *   in by inclusion-exclusion: pre[i+1][j+1] = matrix[i][j] + pre[i][j+1] + pre[i+1][j] - pre[i][j].
 *   A query rectangle is then the big prefix block minus the strip above it minus the strip to
 *   its left plus the top-left corner added back (counted twice by the two subtractions):
 *   pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1]. Construction is one pass over
 *   the matrix; every query is four array reads.
 *
 * Overflow: a full-matrix sum reaches m*n*max|v| = 200*200*1e4 = 4e8 (< int max), but the
 *   prefix table is 64-bit so the four-term combination never overflows mid-computation.
 *
 * Complexity: O(m * n) construction, O(1) per query; O(m * n) space.
 */

#include <vector>
using namespace std;

class NumMatrix {
    vector<vector<long long>> pre;         // pre[i][j] = sum of matrix[0..i-1][0..j-1]

public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = (int)matrix.size();
        int n = m ? (int)matrix[0].size() : 0;
        pre.assign(m + 1, vector<long long>(n + 1, 0));   // zero border row/column
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                // area up to (i,j) = cell + area above + area left - doubly-counted overlap
                pre[i + 1][j + 1] = matrix[i][j] + pre[i][j + 1] + pre[i + 1][j] - pre[i][j];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        // Inclusion-exclusion over the four prefix corners bounding the rectangle.
        return (int)(pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1]
                     - pre[row2 + 1][col1] + pre[row1][col1]);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
