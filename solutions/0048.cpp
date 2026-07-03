/*
 * LeetCode 48 - Rotate Image
 *
 * Given an n x n matrix representing an image, rotate it 90 degrees clockwise.
 * The rotation must be done IN PLACE: the input matrix is modified directly and
 * no second n x n matrix may be allocated to hold the result.
 *
 * Input  : vector<vector<int>>& matrix - an n x n grid, modified in place.
 * Output : none - matrix is mutated to its 90-degree clockwise rotation.
 *
 * Constraints: n == matrix.length == matrix[i].length; 1 <= n <= 20;
 *   -1000 <= matrix[i][j] <= 1000.
 *
 * Approach: a 90-degree clockwise rotation factors into two in-place passes -
 *   transpose, then reverse each row. Transposing reflects the grid across its
 *   main diagonal, mapping cell (i, j) to (j, i). Reversing each row afterward
 *   sends (j, i) to (j, n - 1 - i), and (i, j) -> (j, n - 1 - i) is precisely
 *   where a clockwise turn should place the original element. Neither pass needs
 *   an auxiliary matrix, so the O(1) extra-space in-place requirement is met.
 *
 * Complexity: O(n^2) time - every cell is touched a constant number of times;
 *   O(1) extra space - only index variables, all swaps happen within `matrix`.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();

        // Step 1 - transpose. Swap each pair (i, j) with (j, i). Restricting j
        // to the strict upper triangle (j > i) ensures every off-diagonal pair
        // is swapped exactly once and the diagonal stays put.
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                swap(matrix[i][j], matrix[j][i]);

        // Step 2 - reverse every row. Combined with the transpose above, this
        // moves original (i, j) to (j, n - 1 - i): the 90-degree clockwise spot.
        for (int i = 0; i < n; ++i)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};
