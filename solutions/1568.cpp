/*
 * LeetCode 1568 - Minimum Number of Days to Disconnect Island
 *
 * A binary grid has 1 = land, 0 = water; an island is a maximal 4-directionally
 * connected group of land cells. The grid is "connected" when it holds EXACTLY one
 * island and "disconnected" otherwise (zero islands, or two or more). Each day one
 * land cell may be turned into water. Return the minimum number of days needed to
 * make the grid disconnected.
 *
 * Input  : vector<vector<int>>& grid (m x n, entries 0/1). Output : int — min days.
 *
 * Constraints: 1 <= m, n <= 30. Small grid, so recounting islands many times is
 *   cheap.
 *
 * Approach: the answer is always 0, 1, or 2.
 *   - 0 if the grid is already disconnected (island count != 1).
 *   - Otherwise there is exactly one island. If some single land cell is an
 *     articulation point, removing it splits the island, so the answer is 1; try
 *     every land cell once.
 *   - Otherwise the answer is 2, and 2 always suffices: take the top-left-most land
 *     cell, which has at most two land neighbours (right and down); removing those
 *     two isolates it (or empties a tiny island), guaranteeing disconnection.
 *   Island counting is a flood fill over a fresh visited matrix, leaving the grid
 *   intact; the single-cell test mutates one cell, recounts, then restores it.
 *
 * Complexity: O((m*n)^2) time — an O(m*n) island count for each of up to m*n land
 *   cells removed. O(m*n) space for the visited matrix and recursion.
 */

#include <vector>
using namespace std;

class Solution {
    int m, n;

    // Flood-fill one island starting at (i, j), marking visited cells.
    void dfs(const vector<vector<int>>& g, vector<vector<char>>& vis, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || g[i][j] == 0 || vis[i][j])
            return;
        vis[i][j] = 1;
        dfs(g, vis, i + 1, j);
        dfs(g, vis, i - 1, j);
        dfs(g, vis, i, j + 1);
        dfs(g, vis, i, j - 1);
    }

    // Number of 4-connected land components; does not modify the grid.
    int countIslands(const vector<vector<int>>& g) {
        vector<vector<char>> vis(m, vector<char>(n, 0));
        int islands = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (g[i][j] == 1 && !vis[i][j]) {
                    ++islands;
                    dfs(g, vis, i, j);
                }
        return islands;
    }

public:
    int minDays(vector<vector<int>>& grid) {
        m = (int)grid.size();
        n = (int)grid[0].size();

        // Day 0: already disconnected (0 islands, or 2+).
        if (countIslands(grid) != 1)
            return 0;

        // Day 1: is there a single land cell whose removal disconnects the island?
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;                 // tentatively remove this cell
                    if (countIslands(grid) != 1) {
                        grid[i][j] = 1;             // restore before returning
                        return 1;
                    }
                    grid[i][j] = 1;                 // restore and keep searching
                }

        // Day 2 always works: removing two cells can isolate a corner land cell.
        return 2;
    }
};
