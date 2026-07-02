/*
 * LeetCode 2812 - Find the Safest Path in a Grid
 *
 * An n x n grid marks thief cells with 1. Starting at (0, 0) and moving in the
 * four cardinal directions, reach (n - 1, n - 1). The safeness factor of a
 * path is the smallest Manhattan distance from any cell on the path to any
 * thief. Return the maximum safeness factor achievable — i.e. pick the path
 * whose closest approach to a thief is as large as possible.
 *
 * Input  : vector<vector<int>>& grid — n x n matrix of 0/1 (1 = thief).
 * Output : int — maximum safeness factor over all (0,0) -> (n-1,n-1) paths.
 *
 * Constraints: 1 <= n <= 400; grid[i][j] is 0 or 1; at least one thief exists.
 *
 * Approach: two classic phases.
 *   1) Multi-source BFS seeded with every thief at distance 0 computes, for
 *      each cell, the distance to its nearest thief. Movement is unobstructed,
 *      so BFS grid distance equals the Manhattan distance from the statement.
 *   2) "Maximize the minimum along a path" is a monotonic predicate: if some
 *      path keeps distance >= k everywhere, paths also exist for every k' < k.
 *      Binary search the answer k, testing feasibility with a BFS restricted
 *      to cells whose thief distance is >= k. The search range is
 *      [0, min(dist at start, dist at goal)] because every path contains both
 *      endpoints, and k = 0 is always feasible.
 *
 * Complexity: each BFS is O(n^2); the binary search adds a log factor over the
 *   distance range (at most 2n), giving O(n^2 log n) time — roughly 1.6M cell
 *   visits for n = 400. Space is O(n^2) for the distance grid and BFS queues.
 */

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    static constexpr int DR[4] = {1, -1, 0, 0};
    static constexpr int DC[4] = {0, 0, 1, -1};

public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = (int)grid.size();

        // Phase 1 — distance from every cell to its nearest thief.
        // Seeding the queue with all thieves at once (multi-source BFS) means
        // each cell is first reached by, and labeled with, its closest thief.
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (int d = 0; d < 4; ++d) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Phase 2 — binary search the answer. No path can beat the distance at
        // its own endpoints, so hi starts at min(dist[start], dist[goal]).
        // A thief sitting on (0,0) or (n-1,n-1) collapses the range to 0.
        int lo = 0, hi = min(dist[0][0], dist[n - 1][n - 1]);
        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;      // round up so lo = mid progresses
            if (reachable(dist, n, mid)) lo = mid; // mid feasible: try higher
            else hi = mid - 1;                     // infeasible: go lower
        }
        return lo;
    }

private:
    // Can we walk (0,0) -> (n-1,n-1) stepping only on cells at distance >= k
    // from every thief? Plain BFS over the allowed cells.
    bool reachable(const vector<vector<int>>& dist, int n, int k) {
        if (dist[0][0] < k) return false;
        vector<vector<char>> seen(n, vector<char>(n, 0));
        queue<pair<int, int>> q;
        q.push({0, 0});
        seen[0][0] = 1;
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            if (r == n - 1 && c == n - 1) return true;
            for (int d = 0; d < 4; ++d) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n
                    && !seen[nr][nc] && dist[nr][nc] >= k) {
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
        return false;
    }
};
