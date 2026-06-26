/*
 * LeetCode 1584 - Min Cost to Connect All Points
 *
 * Given n distinct points on a 2D plane, the cost of an edge between two points is
 * their Manhattan distance |xi - xj| + |yi - yj|. Connect all points into a single
 * tree (exactly one simple path between any pair) at minimum total cost — i.e. find
 * the weight of a Minimum Spanning Tree of the complete graph on these points.
 *
 * Input  : vector<vector<int>>& points, points[i] = {x, y}.
 * Output : int — minimum total connection cost.
 *
 * Constraints: 1 <= n <= 1000; -10^6 <= xi, yi <= 10^6; all points distinct.
 *
 * Approach: the graph is complete (every pair is an edge), so the dense O(n^2)
 *   variant of Prim's algorithm is the natural choice — it needs no edge list and
 *   no heap. Keep minDist[v] = the cheapest edge linking v to the tree built so far.
 *   Each round, pick the not-yet-added vertex with the smallest minDist, add its
 *   cost to the answer, then relax minDist[w] = min(minDist[w], dist(u, w)) for all
 *   remaining w. After n rounds every point is connected and the accumulated cost is
 *   the MST weight. Building the ~n^2/2 edges explicitly (Kruskal) would also work
 *   but costs more memory; dense Prim fits the complete-graph shape better.
 *
 * Complexity: O(n^2) time (n selections, each scanning n vertices) and O(n) space.
 *   An individual edge is at most 4*10^6; the MST total stays near 10^8 for points
 *   in a 2*10^6 box, but the sum is accumulated in 64-bit out of caution.
 */

#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = (int)points.size();
        if (n <= 1) return 0;                 // a single point needs no edges

        vector<int> minDist(n, INT_MAX);      // cheapest edge from v to the tree
        vector<bool> inMST(n, false);         // whether v is already connected
        minDist[0] = 0;                       // seed the tree with point 0
        long long total = 0;

        for (int iter = 0; iter < n; ++iter) {
            // Select the closest frontier vertex not yet in the tree.
            int u = -1;
            for (int v = 0; v < n; ++v)
                if (!inMST[v] && (u == -1 || minDist[v] < minDist[u]))
                    u = v;

            inMST[u] = true;
            total += minDist[u];              // add the edge that attaches u

            // Relax every outside vertex against the newly added point u.
            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int d = abs(points[u][0] - points[v][0])
                          + abs(points[u][1] - points[v][1]);
                    if (d < minDist[v]) minDist[v] = d;
                }
            }
        }
        return (int)total;                    // provably fits in int (~10^8 max)
    }
};
