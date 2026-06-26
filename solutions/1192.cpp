/*
 * LeetCode 1192 - Critical Connections in a Network
 *
 * n servers (0..n-1) are joined by undirected connections forming a connected
 * network. A connection is "critical" if removing it disconnects some pair of
 * servers. Return every critical connection. A critical connection is exactly a
 * BRIDGE of the graph: an edge that lies on no cycle.
 *
 * Input  : int n, vector<vector<int>>& connections (edge list). Output :
 *          vector<vector<int>> listing every bridge, endpoints in any order.
 *
 * Constraints: 2 <= n <= 10^5; n-1 <= |connections| <= 10^5; no repeated edges.
 *   With up to 10^5 nodes the DFS recursion could be 10^5 deep, which can overflow
 *   the call stack, so the depth-first search here is written ITERATIVELY.
 *
 * Approach: Tarjan's bridge-finding. A DFS assigns each node a discovery time
 *   disc[u] and a low-link low[u] = the smallest discovery time reachable from u's
 *   DFS subtree using tree edges plus at most one back edge. For a tree edge
 *   (u -> v), after exploring v we relax low[u] by low[v]; if low[v] > disc[u]
 *   then v's subtree has no back edge climbing to u or above, so (u, v) is a bridge.
 *   A back edge (u -> already-visited w, w not the parent) relaxes low[u] by
 *   disc[w]. The recursion is simulated with an explicit stack of frames, each
 *   remembering the node, its parent, and how far its adjacency list has been
 *   scanned, so the search resumes correctly after a child finishes. The single
 *   edge back to the parent is skipped (the input has no repeated edges).
 *
 * Complexity: O(n + m) time and O(n + m) space for the adjacency list, the disc/
 *   low arrays, and the explicit DFS stack.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    // One simulated recursion frame: the node, the parent it was entered from,
    // and how far its adjacency list has been scanned so far.
    struct Frame { int node, parent, idx; };

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Build the undirected adjacency list.
        vector<vector<int>> adj(n);
        for (const auto& e : connections) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> disc(n, -1), low(n, 0);     // disc[u] == -1 means unvisited
        vector<vector<int>> bridges;
        vector<Frame> dfs;                       // explicit DFS stack (avoids deep recursion)
        int timer = 0;

        // One explicit-stack DFS per component (the network is connected, but the
        // loop costs nothing and guards against any disconnected input).
        for (int s = 0; s < n; ++s) {
            if (disc[s] != -1)
                continue;

            disc[s] = low[s] = timer++;
            dfs.push_back({s, -1, 0});

            while (!dfs.empty()) {
                // Capture the current frame's node/parent; mutate its scan index in
                // place. Locals are taken first so a reallocation on push_back below
                // cannot dangle a reference.
                int u = dfs.back().node;
                int parent = dfs.back().parent;

                if (dfs.back().idx < (int)adj[u].size()) {
                    int v = adj[u][dfs.back().idx++];

                    if (v == parent)
                        continue;               // skip the lone edge back to parent

                    if (disc[v] == -1) {
                        // Tree edge: descend into v.
                        disc[v] = low[v] = timer++;
                        dfs.push_back({v, u, 0});
                    } else {
                        // Back edge: v is an ancestor (or cross within subtree).
                        low[u] = min(low[u], disc[v]);
                    }
                } else {
                    // Finished u: fold its low-link into its parent and test bridge.
                    dfs.pop_back();
                    if (parent != -1) {
                        low[parent] = min(low[parent], low[u]);
                        if (low[u] > disc[parent])
                            bridges.push_back({parent, u});
                    }
                }
            }
        }

        return bridges;
    }
};
