/*
 * LeetCode 1976 - Number of Ways to Arrive at Destination
 *
 * A city has n intersections (0..n-1) joined by bidirectional weighted roads; the graph is
 * connected with at most one road between any pair. Count how many distinct paths go from
 * intersection 0 to intersection n-1 in the SHORTEST possible total time, and return that
 * count modulo 1e9 + 7.
 *
 * Input  : int n, vector<vector<int>> roads (each {u, v, time}).
 * Output : int — number of shortest-time 0 -> n-1 paths, mod 1e9 + 7.
 *
 * Constraints: 1 <= n <= 200, n-1 <= roads.length <= n(n-1)/2, 1 <= time <= 1e9, connected.
 *
 * Approach: Dijkstra from node 0 carrying a path counter. Keep dist[v] (shortest time, 64-bit)
 *   and ways[v] (number of shortest paths to v, mod p). When relaxing an edge (u, v, w) from a
 *   just-finalized u:
 *     - if dist[u] + w < dist[v]: found a strictly shorter route, so dist[v] updates and
 *       ways[v] resets to ways[u];
 *     - if dist[u] + w == dist[v]: another shortest route through u, so ways[v] += ways[u].
 *   This is correct because every road takes time >= 1, so any predecessor on a shortest path
 *   has strictly smaller distance and is finalized (popped) before v; hence ways[u] is complete
 *   when u is popped and its contribution to ways[v] is counted exactly once. The answer is
 *   ways[n-1].
 *
 * Overflow: a path can sum up to ~ (n-1) * max time = 199 * 1e9 ~ 2e11, so distances are
 *   64-bit; the counter stays < p and is reduced after each addition.
 *
 * Complexity: O((V + E) log V) time, O(V + E) space.
 */

#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const long long MOD = 1000000007;

        // Adjacency list: adj[u] holds (neighbor, weight).
        vector<vector<pair<int, long long>>> adj(n);
        for (const auto& r : roads) {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        vector<long long> dist(n, LLONG_MAX);   // shortest time to each node
        vector<long long> ways(n, 0);           // number of shortest paths, mod p
        dist[0] = 0;
        ways[0] = 1;

        // Min-heap of (distance, node); lazy deletion via the stale-entry check below.
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;          // outdated entry -> u already finalized

            for (const auto& [v, w] : adj[u]) {
                long long nd = d + w;           // d is finite (u finalized), so no overflow
                if (nd < dist[v]) {             // strictly better route to v
                    dist[v] = nd;
                    ways[v] = ways[u];          // its shortest-path count starts fresh from u
                    pq.push({nd, v});
                } else if (nd == dist[v]) {     // another shortest route to v
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }
        return (int)ways[n - 1];
    }
};
