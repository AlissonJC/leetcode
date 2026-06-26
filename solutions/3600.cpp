/*
 * LeetCode 3600 - Maximize Spanning Tree Stability with Upgrades
 *
 * n nodes (0..n-1) and a list of undirected edges edges[i] = [u, v, s, must].
 * s is the edge strength; must == 1 forces the edge into the spanning tree and
 * forbids upgrading it. With at most k upgrades — each doubles one optional
 * (must == 0) edge's strength, each such edge upgradable once — build a spanning
 * tree maximizing its stability, defined as the minimum strength among its edges.
 * Return that maximum stability, or -1 if the nodes cannot be connected.
 *
 * Input  : int n, vector<vector<int>>& edges, int k.
 * Output : int — best achievable stability, or -1.
 *
 * Constraints: 2 <= n <= 1e5; 1 <= edges.length <= 1e5; 1 <= s <= 1e5; must in
 *              {0,1}; 0 <= k <= n; no duplicate edges.
 *
 * Approach: maximize-the-minimum, so binary search the answer x and test
 *   feasibility with a union-find. Every must edge is in the tree and cannot be
 *   upgraded, so it caps the answer at the smallest must-edge strength; if the must
 *   edges themselves form a cycle, no spanning tree can contain them all -> -1.
 *   For a threshold x: reject if any must edge is below x. Otherwise union all must
 *   edges plus every optional edge already at strength >= x (these cost nothing),
 *   then union optional edges with s < x <= 2s, each consuming one upgrade. x is
 *   feasible when the graph becomes fully connected using at most k upgrades.
 *   Feasibility is monotonic in x (a lower threshold only makes more edges usable
 *   and the must-edge cap easier), so binary search finds the largest feasible x.
 *
 * Complexity: O((n + m) * log(maxStrength)) time, O(n) space — about 18 union-find
 *   passes over n nodes and m edges.
 */

#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        parent.resize(n);
        rnk.resize(n);

        // Pre-pass: must edges must be acyclic, and the weakest must edge caps the
        // answer (it is always present and never upgradable).
        reset(n);
        int mustMin = INT_MAX, maxS = 1;
        for (const auto& e : edges) {
            maxS = max(maxS, e[2]);
            if (e[3] == 1) {
                if (find(e[0]) == find(e[1])) return -1;   // mandatory edges form a cycle
                unite(e[0], e[1]);
                mustMin = min(mustMin, e[2]);
            }
        }

        // Largest feasible stability via binary search; upper bound is a doubled
        // optional edge (2*maxS), lower bound the minimum strength 1.
        int lo = 1, hi = 2 * maxS, ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(n, edges, k, mid, mustMin)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    }

private:
    vector<int> parent, rnk;
    int comps = 0;

    void reset(int n) {
        for (int i = 0; i < n; ++i) { parent[i] = i; rnk[i] = 0; }
        comps = n;
    }
    int find(int x) {
        while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;                 // already connected: no merge
        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) ++rnk[a];
        --comps;
        return true;
    }

    bool feasible(int n, vector<vector<int>>& edges, int k, int x, int mustMin) {
        // A must edge below x would force the stability under x.
        if (mustMin < x) return false;
        reset(n);

        // Forced must edges and optional edges already strong enough cost nothing.
        for (const auto& e : edges)
            if (e[3] == 1 || e[2] >= x) unite(e[0], e[1]);

        // Optional edges reaching x only after one upgrade (s < x <= 2s): each
        // merge they perform spends exactly one upgrade.
        int used = 0;
        for (const auto& e : edges)
            if (e[3] == 0 && e[2] < x && 2 * e[2] >= x)
                if (unite(e[0], e[1]) && ++used > k)
                    return false;                 // upgrade budget exhausted

        return comps == 1;                        // all nodes connected
    }
};
