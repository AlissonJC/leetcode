/*
 * LeetCode 3620 - Network Recovery Pathways
 *
 * A directed acyclic graph has n nodes numbered 0..n-1. Each edge
 * edges[i] = [u, v, cost] is a one-way link u -> v with a recovery cost.
 * Some nodes are offline; online[i] tells whether node i is up, and nodes 0
 * and n-1 are always online. A path from 0 to n-1 is valid when every
 * intermediate node is online AND the sum of its edge costs does not exceed
 * the budget k. A valid path's "score" is the MINIMUM edge cost along it.
 * Return the largest achievable score over all valid paths, or -1 if none.
 *
 * Input  : vector<vector<int>> edges ([u, v, cost]); vector<bool> online;
 *          long long k (cost budget).
 * Output : int - the maximum, over valid paths, of the minimum edge cost;
 *          -1 when no valid path exists.
 *
 * Constraints: 2 <= n <= 5*10^4; 0 <= m == edges.length <= min(10^5,
 *   n*(n-1)/2); 0 <= cost <= 10^9; 0 <= k <= 5*10^13; the graph is a DAG;
 *   online[0] and online[n-1] are both true.
 *
 * Approach: this is a classic "maximize the minimum edge" objective, so
 *   binary search the answer. Fix a threshold x and keep only edges whose
 *   cost is >= x. On that restricted graph EVERY 0 -> (n-1) path already has
 *   score >= x, so the only remaining question is whether one of them fits
 *   the budget - i.e. whether the CHEAPEST such path costs <= k. Because the
 *   graph is a DAG, that cheapest total cost is a single-source shortest path
 *   computed by relaxing edges in topological order (dp[v] = min cost to reach
 *   v from 0 using allowed edges and only online nodes). feasible(x) can only
 *   flip from true to false as x grows - raising the bar removes edges, never
 *   adds them - so it is monotone and binary-searchable. Every path's score
 *   is a real edge cost, hence the largest feasible integer threshold equals
 *   the answer exactly. If even x = 0 (all edges allowed) admits no path
 *   within budget, there is no valid path at all, so return -1.
 *
 * Complexity: O((n + m) * log C) time, where C is the maximum edge cost
 *   (<= 10^9, so ~30 feasibility checks), each check an O(n + m) DAG DP;
 *   O(n + m) space for the adjacency list, topological order, and dp table.
 */

#include <vector>
#include <utility>
#include <climits>
using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = (int)online.size();

        // Adjacency list adj[u] = list of (v, cost), plus in-degrees so we can
        // build a topological order via Kahn's algorithm. Track the largest
        // edge cost to bound the binary search on the answer.
        vector<vector<pair<int, int>>> adj(n);
        vector<int> indeg(n, 0);
        int maxCost = 0;
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            ++indeg[v];
            if (w > maxCost) maxCost = w;
        }

        // Kahn's algorithm: repeatedly emit a node with no unprocessed
        // predecessors. Guaranteed to cover all n nodes since the graph is a
        // DAG. Processing dp in this order lets each dp[u] settle before any
        // edge leaving u is relaxed.
        vector<int> order;
        order.reserve(n);
        vector<int> ready;
        for (int i = 0; i < n; ++i)
            if (indeg[i] == 0) ready.push_back(i);
        while (!ready.empty()) {
            int u = ready.back();
            ready.pop_back();
            order.push_back(u);
            for (const auto& [v, w] : adj[u])
                if (--indeg[v] == 0) ready.push_back(v);
        }

        // Path totals reach m * maxCost ~ 10^5 * 10^9 = 10^14 and k can be
        // 5*10^13, so distances must be 64-bit. INF stays far below overflow
        // and is never used as an operand (INF nodes are skipped).
        const long long INF = LLONG_MAX / 4;
        vector<long long> dp(n);

        // feasible(x): is there a 0 -> (n-1) path using only edges of cost >= x
        // and only online intermediate nodes, with total cost <= k? Answered by
        // the minimum-cost path on that restricted DAG.
        auto feasible = [&](int x) -> bool {
            for (int i = 0; i < n; ++i) dp[i] = INF;
            dp[0] = 0;
            for (int u : order) {
                if (dp[u] == INF) continue;   // node 0's component not reached here
                if (!online[u]) continue;     // cannot route a path THROUGH an offline node
                long long du = dp[u];
                for (const auto& [v, w] : adj[u]) {
                    if (w < x) continue;      // edge too cheap: it would drop the score below x
                    if (du + w < dp[v]) dp[v] = du + w;
                }
            }
            return dp[n - 1] <= k;
        };

        // If the loosest possible threshold (x = 0, every edge allowed) still
        // cannot reach n-1 within budget, no valid path exists.
        if (!feasible(0)) return -1;

        // Binary search the largest feasible threshold. x = 0 is already known
        // to work, so the answer is at least 0.
        int lo = 1, hi = maxCost, ans = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
