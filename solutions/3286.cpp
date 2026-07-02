/*
 * LeetCode 3286 - Find a Safe Walk Through a Grid
 *
 * You start at (0, 0) of an m x n binary grid with a given amount of health
 * and want to reach (m - 1, n - 1), moving up/down/left/right while your
 * health stays positive. Every cell with grid[i][j] = 1 is unsafe and drains
 * 1 health when stepped on — the start and end cells included. Return true if
 * the final cell can be reached with a health value of 1 or more.
 *
 * Input  : vector<vector<int>> grid (entries 0/1); int health.
 * Output : bool — can the walk end with health >= 1?
 *
 * Constraints: 1 <= m, n <= 50; 2 <= m * n; 1 <= health <= m + n;
 *   grid[i][j] is either 0 or 1.
 *
 * Approach: the health lost along a walk is exactly the number of 1-cells it
 *   steps on, so the question reduces to "what is the MINIMUM damage over all
 *   paths from (0,0) to (m-1,n-1)?" — a shortest-path problem where entering
 *   a cell costs its grid value (0 or 1), plus the start cell's own value.
 *   With only 0/1 edge weights, 0-1 BFS applies: keep a deque and, when a
 *   relaxation improves a neighbor, push it to the FRONT for a 0-cost edge and
 *   to the BACK for a 1-cost edge. The deque then always holds cells in
 *   non-decreasing distance order (at most two distinct values at once), so
 *   every cell settles at its true minimum as in Dijkstra, without the
 *   priority-queue log factor. Health only decreases while walking, so it is
 *   lowest at the very end — if the final health is >= 1, it was positive at
 *   every intermediate step too; comparing the total minimum damage against
 *   health once is enough.
 *
 * Complexity: O(m * n) time — each of the O(m * n) unit-capped relaxations is
 *   O(1); O(m * n) space for the distance table and the deque.
 */

#include <vector>
#include <deque>
#include <utility>
#include <climits>
using namespace std;

class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = (int)grid.size(), n = (int)grid[0].size();

        // dist[r][c] = minimum total damage to stand on (r, c), counting the
        // start cell itself (walking begins ON (0,0), so its 1 already costs).
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = grid[0][0];

        deque<pair<int, int>> dq;
        dq.push_back({0, 0});

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                int nd = dist[r][c] + grid[nr][nc];
                if (nd < dist[nr][nc]) {
                    dist[nr][nc] = nd;
                    // 0-1 BFS ordering: free moves keep priority (front),
                    // damaging moves wait behind the current layer (back).
                    if (grid[nr][nc] == 0) dq.push_front({nr, nc});
                    else                   dq.push_back({nr, nc});
                }
            }
        }

        // Need health - damage >= 1, i.e. strictly fewer 1-cells than health.
        return dist[m - 1][n - 1] < health;
    }
};
