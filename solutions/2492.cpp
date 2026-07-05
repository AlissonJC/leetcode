/*
 * LeetCode 2492 - Minimum Score of a Path Between Two Cities
 *
 * Cities 1..n are joined by bidirectional roads; roads[i] = {a, b, dist} is a road
 * of length dist between cities a and b. The graph need not be connected. The
 * "score" of a path is the smallest road length used along it. A path may reuse
 * roads and revisit cities freely. Return the minimum achievable score of any path
 * between city 1 and city n (guaranteed to share a connected component).
 *
 * Input  : int n, vector<vector<int>>& roads (each entry {a, b, dist}).
 * Output : int -- minimum possible path score between city 1 and city n.
 *
 * Constraints: 2 <= n <= 1e5; 1 <= roads.length <= 1e5; 1 <= dist <= 1e4;
 *   a != b; no repeated edges; at least one path connects 1 and n.
 *
 * Approach: because roads may be traversed any number of times, a path from 1 to n
 *   can detour across *any* road that lies in city 1's connected component and then
 *   walk straight back -- every such road's length therefore enters the multiset of
 *   traversed lengths, so the score (their minimum) can be pushed down to it.
 *   Conversely, no road outside the component is ever reachable. Hence the answer is
 *   simply the lightest road with both endpoints in the component containing cities
 *   1 and n. Flood that component with a BFS from city 1 and keep the minimum length
 *   over every road seen from a reachable city.
 *
 * Complexity: O(n + m) time and space, m = roads.length -- one BFS over the
 *   component plus a scan of its incident edges. Lengths fit in int (<= 1e4), so a
 *   plain int running minimum suffices.
 */

#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Adjacency list keyed by city; each entry is (neighbor, road length).
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& r : roads) {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        // Standard BFS flood starting at city 1. City n lives in the same component
        // by the problem guarantee, so we never need to search from n separately.
        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(1);
        visited[1] = true;

        int ans = INT_MAX;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& [v, w] : adj[u]) {
                // Any edge incident to a reachable city belongs to the component, so
                // its length is a valid candidate score -- record it before deciding
                // whether the far endpoint still needs to be enqueued.
                ans = min(ans, w);
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return ans;
    }
};
