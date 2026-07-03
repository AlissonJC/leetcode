/*
 * LeetCode 59 - Spiral Matrix II
 *
 * Given a positive integer n, generate an n x n matrix filled with the integers
 * from 1 to n^2 placed in clockwise spiral order, starting at the top-left
 * corner and spiraling inward.
 *
 * Input  : int n - the side length of the square matrix.
 * Output : vector<vector<int>> - the n x n matrix filled in spiral order.
 *
 * Constraints: 1 <= n <= 20.
 *
 * Approach: trace the spiral path directly, writing the next consecutive integer
 *   at each visited cell. Maintain a heading that cycles right -> down -> left ->
 *   up and a current position. Before stepping, peek at the cell straight ahead;
 *   if it falls off the board or has already been written, rotate the heading
 *   90 degrees clockwise and step that way instead. Since the matrix begins
 *   zero-filled, "already written" is simply a nonzero cell, so that one check
 *   drives every turn and carves the inward spiral automatically. Writing values
 *   1..n^2 in order lands each number in its spiral position.
 *
 * Complexity: O(n^2) time - exactly one write per cell; O(1) extra space beyond
 *   the returned matrix (values 1..n^2 <= 400 fit comfortably in int).
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        // Zero-filled grid; a 0 marks an unwritten cell, the turn signal below.
        vector<vector<int>> m(n, vector<int>(n, 0));

        // Heading deltas in clockwise order: right, down, left, up.
        const int dr[4] = {0, 1, 0, -1};
        const int dc[4] = {1, 0, -1, 0};

        int r = 0, c = 0, dir = 0;
        for (int val = 1; val <= n * n; ++val) {
            m[r][c] = val;

            // Look one step ahead in the current heading.
            int nr = r + dr[dir], nc = c + dc[dir];

            // Turn clockwise if the next cell is out of bounds or already filled.
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || m[nr][nc] != 0) {
                dir = (dir + 1) % 4;
                nr = r + dr[dir];
                nc = c + dc[dir];
            }

            r = nr;
            c = nc;
        }

        return m;
    }
};
