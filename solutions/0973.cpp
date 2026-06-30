/*
 * LeetCode 973 - K Closest Points to Origin
 *
 * Given points on the X-Y plane (points[i] = {x, y}) and an integer k, return the k
 * points closest to the origin (0, 0) under Euclidean distance. The k points may be
 * returned in any order, and the set of answers is guaranteed to be unique.
 *
 * Input  : vector<vector<int>> points; int k. Output : the k closest points.
 *
 * Constraints: 1 <= k <= points.length <= 1e4; -1e4 <= x, y <= 1e4. The squared
 *   distance reaches 2*(1e4)^2 = 2e8, which fits in a 32-bit int, but it is computed in
 *   64-bit to keep the comparison obviously overflow-free.
 *
 * Approach: ranking by Euclidean distance is the same as ranking by squared distance
 *   x^2 + y^2, so the costly sqrt is never needed. Rather than fully sorting, use a
 *   selection (nth_element / introselect) keyed on squared distance: it rearranges the
 *   array so the element that belongs at index k-1 is in place and, as a side effect,
 *   the first k entries are the k smallest (in arbitrary order) and all are <= the rest.
 *   Returning that prefix gives the k closest points.
 *
 * Complexity: O(n) average time (introselect), O(1) extra space beyond the output;
 *   the comparator is O(1).
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Squared distance to the origin; 64-bit so x^2 + y^2 cannot overflow.
        auto d2 = [](const vector<int>& p) -> long long {
            return (long long)p[0] * p[0] + (long long)p[1] * p[1];
        };

        // Place the k-th closest at index k-1; everything before it is no farther.
        nth_element(points.begin(), points.begin() + (k - 1), points.end(),
                    [&](const vector<int>& a, const vector<int>& b) {
                        return d2(a) < d2(b);
                    });

        // The first k points are exactly the k closest (order within them is irrelevant).
        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};
