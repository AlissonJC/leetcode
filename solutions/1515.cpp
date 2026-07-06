/*
 * LeetCode 1515 - Best Position for a Service Centre
 *
 * Given the 2D positions of customers, place a service centre (xc, yc) so that the sum of
 * Euclidean distances from the centre to every customer is minimized, and return that
 * minimum sum. This point is the geometric median (Weber point) of the customers.
 *
 * Input  : vector<vector<int>> positions, positions[i] = {xi, yi}.
 * Output : the minimum achievable total Euclidean distance (answers within 1e-5 accepted).
 *
 * Constraints: 1 <= positions.length <= 50; 0 <= xi, yi <= 100.
 *
 * Approach: the objective f(x, y) = sum of sqrt((x-xi)^2 + (y-yi)^2) is a sum of Euclidean
 *   norms, hence convex, so it has a single global minimum and any strictly descending
 *   search reaches it. Use pattern (compass) search: start at the centroid, and repeatedly
 *   try stepping the current point by +-step along each axis; move to the first neighbour
 *   that lowers f. When no axis move helps, halve the step to probe finer. The four axis
 *   directions positively span the plane, so a point where none of them improves at an
 *   arbitrarily small step is a stationary point, which for a convex f is the global
 *   optimum. Shrinking the step from 100 down to 1e-8 pins the answer far tighter than the
 *   required 1e-5 tolerance. The geometric median lies inside the convex hull, so starting
 *   at the centroid keeps the search near the target from the outset.
 *
 * Complexity: O(iterations * n); iterations is a small constant (~tens of step halvings,
 *   each with a few moves), so effectively O(n) per solve. O(1) extra space.
 */

#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = (int)positions.size();

        // Total Euclidean distance from (x, y) to all customers.
        auto totalDist = [&](double x, double y) {
            double sum = 0.0;
            for (auto& p : positions) {
                double dx = x - p[0], dy = y - p[1];
                sum += sqrt(dx * dx + dy * dy);
            }
            return sum;
        };

        // Start at the centroid — a good interior guess for the geometric median.
        double x = 0.0, y = 0.0;
        for (auto& p : positions) { x += p[0]; y += p[1]; }
        x /= n; y /= n;

        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};
        const double eps = 1e-8;
        double step = 100.0;                 // large enough to cover the whole coordinate range
        double cur = totalDist(x, y);

        while (step > eps) {
            bool improved = false;
            for (int d = 0; d < 4; ++d) {
                double nx = x + dx[d] * step;
                double ny = y + dy[d] * step;
                double nd = totalDist(nx, ny);
                if (nd < cur) {              // descend to the first improving neighbour
                    x = nx; y = ny; cur = nd;
                    improved = true;
                    break;
                }
            }
            if (!improved)
                step /= 2.0;                 // no axis move helps: refine the probe size
        }
        return cur;
    }
};
