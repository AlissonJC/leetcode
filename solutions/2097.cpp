/*
 * LeetCode 2097 - Valid Arrangement of Pairs
 *
 * Given a 0-indexed array pairs where pairs[i] = [start_i, end_i], reorder all the
 * pairs into a sequence so that consecutive pairs chain up: end_{i-1} == start_i for
 * every i >= 1. Return any such arrangement; the input is guaranteed to allow one.
 *
 * Input  : vector<vector<int>>& pairs. Output : vector<vector<int>> — a valid order.
 *
 * Constraints: 1 <= pairs.length <= 10^5; 0 <= start_i, end_i <= 10^9; start != end;
 *   no duplicate pairs. Values are large (use hash maps), and the edge count forces
 *   an iterative traversal to avoid deep recursion.
 *
 * Approach: treat each pair [s, e] as a directed edge s -> e. A valid arrangement
 *   is exactly an Eulerian path that walks every edge once, so build it with
 *   Hierholzer's algorithm. The path's starting vertex is the one with one more
 *   outgoing than incoming edge (out - in == 1); if every vertex is balanced the
 *   graph has an Eulerian circuit and any vertex works, so default to pairs[0][0].
 *   Run Hierholzer ITERATIVELY with an explicit stack (edge count up to 1e5 would
 *   blow a recursive stack): repeatedly follow an unused outgoing edge from the
 *   top vertex; when a vertex has none left, pop it into the circuit. Reversing the
 *   popped order yields the vertex sequence, and consecutive vertices form the
 *   arranged edges. Adjacency lives in a hash map since coordinates reach 1e9.
 *
 * Complexity: O(E) time and O(E) space, where E = pairs.length (each edge is pushed
 *   and popped exactly once).
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, vector<int>> adj;        // vertex -> outgoing destinations
        unordered_map<int, int> degDiff;            // out-degree minus in-degree
        adj.reserve(pairs.size() * 2);
        degDiff.reserve(pairs.size() * 2);

        for (const auto& p : pairs) {
            adj[p[0]].push_back(p[1]);
            ++degDiff[p[0]];                        // p[0] gains an outgoing edge
            --degDiff[p[1]];                        // p[1] gains an incoming edge
        }

        // Eulerian path starts at the vertex with out - in == 1; if all balanced
        // (an Eulerian circuit), any start works, so fall back to pairs[0][0].
        int start = pairs[0][0];
        for (const auto& [node, d] : degDiff)
            if (d == 1) { start = node; break; }

        // Iterative Hierholzer: follow unused edges; emit a vertex once it is a
        // dead end. No recursion, so 1e5 edges cannot overflow the call stack.
        vector<int> circuit;
        circuit.reserve(pairs.size() + 1);
        vector<int> stack{start};
        while (!stack.empty()) {
            int v = stack.back();
            auto it = adj.find(v);
            if (it != adj.end() && !it->second.empty()) {
                int u = it->second.back();          // take any remaining edge v -> u
                it->second.pop_back();              // consume it exactly once
                stack.push_back(u);
            } else {
                circuit.push_back(v);               // dead end: finalize this vertex
                stack.pop_back();
            }
        }
        reverse(circuit.begin(), circuit.end());    // post-order was reversed

        // Consecutive vertices in the Euler path are the arranged pairs.
        vector<vector<int>> arrangement;
        arrangement.reserve(pairs.size());
        for (int i = 0; i + 1 < (int)circuit.size(); ++i)
            arrangement.push_back({circuit[i], circuit[i + 1]});
        return arrangement;
    }
};
