/*
 * LeetCode 1489 - Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
 *
 * Given a weighted, undirected, connected graph (n vertices, edges[i] =
 * [a, b, weight]), classify every edge with respect to the graph's minimum
 * spanning trees. A CRITICAL edge appears in every MST: removing it from the graph
 * strictly increases the MST weight (or disconnects the graph). A PSEUDO-CRITICAL
 * edge appears in some but not all MSTs. Return {critical indices, pseudo indices}.
 *
 * Input  : int n, vector<vector<int>>& edges. Output : vector<vector<int>> with two
 *          lists of original edge indices (any order).
 *
 * Constraints: 2 <= n <= 100; 1 <= |edges| <= min(200, n(n-1)/2); weights in
 *   [1, 1000]; all endpoint pairs distinct. Small sizes, so an O(E^2 * alpha)
 *   approach (one MST build per edge per test) is comfortably fast.
 *
 * Approach: Kruskal with forced inclusion / exclusion. First compute the baseline
 *   MST weight. Then for each edge i:
 *     - Critical test: build an MST that is FORBIDDEN to use edge i. If the result
 *       cannot span all n vertices, or its weight exceeds the baseline, then no MST
 *       can avoid edge i, so it is critical.
 *     - Otherwise pseudo-critical test: build an MST that is FORCED to start with
 *       edge i. If that still reaches the baseline weight, some MST contains edge i,
 *       so it is pseudo-critical. (Edges that are neither belong to no MST.)
 *   Edges are sorted by weight once; each MST build is a union-find pass that skips
 *   the excluded edge and pre-unions the forced edge.
 *
 * Complexity: O(E^2 * alpha(n)) time (an O(E) MST build for each of the ~2E tests),
 *   O(E + n) space.
 */

#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
    // Disjoint-set union with union-by-size; find with path compression.
    struct DSU {
        vector<int> parent, size;
        int components;
        DSU(int n) : parent(n), size(n, 1), components(n) {
            iota(parent.begin(), parent.end(), 0);
        }
        int find(int x) {
            while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
            return x;
        }
        bool unite(int a, int b) {
            a = find(a); b = find(b);
            if (a == b) return false;
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a; size[a] += size[b]; --components;
            return true;
        }
    };

    static const int INF = 1e9;

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = (int)edges.size();

        // Pair each edge with its original index, then sort by weight (Kruskal order).
        // order[k] = original index of the k-th lightest edge.
        vector<int> order(m);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&](int x, int y) { return edges[x][2] < edges[y][2]; });

        int baseline = mstWeight(n, edges, order, -1, -1);

        vector<int> critical, pseudo;
        for (int i = 0; i < m; ++i) {
            // (a) Forbid edge i. A higher (or impossible) MST weight means every MST
            //     must use edge i -> critical.
            if (mstWeight(n, edges, order, /*exclude=*/i, /*include=*/-1) > baseline) {
                critical.push_back(i);
            }
            // (b) Force edge i in. Still hitting the baseline means some MST uses it.
            else if (mstWeight(n, edges, order, /*exclude=*/-1, /*include=*/i) == baseline) {
                pseudo.push_back(i);
            }
        }

        return {critical, pseudo};
    }

private:
    // Minimum weight to span all n vertices, with one edge optionally forbidden
    // (exclude) and one edge optionally pre-included (include); both are original
    // edge indices, or -1 if unused. Returns INF if the vertices cannot be spanned.
    static int mstWeight(int n, const vector<vector<int>>& edges, const vector<int>& order,
                         int exclude, int include) {
        DSU dsu(n);
        int weight = 0;

        // Pre-commit the forced edge so the rest of Kruskal works around it.
        if (include != -1) {
            dsu.unite(edges[include][0], edges[include][1]);
            weight += edges[include][2];
        }

        // Greedily add the lightest edges that join two different components.
        for (int idx : order) {
            if (idx == exclude || idx == include)
                continue;
            if (dsu.unite(edges[idx][0], edges[idx][1]))
                weight += edges[idx][2];
        }

        // A spanning tree exists iff everything collapsed into one component.
        return dsu.components == 1 ? weight : INF;
    }
};
