/*
 * LeetCode 54 - Spiral Matrix
 *
 * Given an m x n matrix, return all of its elements in clockwise spiral order:
 * start at the top-left corner, walk right along the top, down the right side,
 * left along the bottom, up the left side, then spiral inward and repeat until
 * every element has been listed.
 *
 * Input  : vector<vector<int>> matrix - an m x n grid.
 * Output : vector<int> - the elements in spiral (clockwise, inward) order.
 *
 * Constraints: m == matrix.length; n == matrix[i].length; 1 <= m, n <= 10;
 *   -100 <= matrix[i][j] <= 100.
 *
 * Approach: track four shrinking boundaries - top, bottom, left, right - and
 *   peel one full ring per outer iteration. Walk the top row left to right, then
 *   the right column top to bottom, then the bottom row right to left, then the
 *   left column bottom to top, tightening the corresponding boundary right after
 *   each pass. The two guards - checking top <= bottom before the bottom row and
 *   left <= right before the left column - are essential: when only a single row
 *   or single column of the ring is left, they stop that middle line from being
 *   emitted twice (the classic spiral double-visit bug). The loop runs while the
 *   boundaries have not crossed.
 *
 * Complexity: O(m * n) time - every cell is appended exactly once; O(1) extra
 *   space beyond the returned vector.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        vector<int> res;
        res.reserve(m * n);

        // Inclusive boundaries of the not-yet-visited sub-rectangle.
        int top = 0, bottom = m - 1, left = 0, right = n - 1;

        while (top <= bottom && left <= right) {
            // Top row, left -> right, then drop it from the rectangle.
            for (int c = left; c <= right; ++c) res.push_back(matrix[top][c]);
            ++top;

            // Right column, top -> bottom, then drop it.
            for (int r = top; r <= bottom; ++r) res.push_back(matrix[r][right]);
            --right;

            // Bottom row, right -> left, only if a row still remains (guard
            // against re-emitting the single leftover row).
            if (top <= bottom) {
                for (int c = right; c >= left; --c) res.push_back(matrix[bottom][c]);
                --bottom;
            }

            // Left column, bottom -> top, only if a column still remains.
            if (left <= right) {
                for (int r = bottom; r >= top; --r) res.push_back(matrix[r][left]);
                ++left;
            }
        }

        return res;
    }
};
