/*
 * LeetCode 391 - Perfect Rectangle
 *
 * Each rectangle is axis-aligned, given as [x, y, a, b] with bottom-left corner
 * (x, y) and top-right corner (a, b). Return true if and only if all the
 * rectangles together form an exact cover of some rectangular region: every
 * point of that region is covered, with no gaps and no overlapping interiors.
 *
 * Input  : vector<vector<int>> rectangles. Output : bool.
 *
 * Constraints: 1 <= n <= 2e4; -1e5 <= x < a <= 1e5; -1e5 <= y < b <= 1e5. A
 *   single area is up to 2e5 * 2e5 = 4e10 and the sum over n rectangles up to
 *   ~8e14, so areas must be accumulated in a 64-bit integer.
 *
 * Approach: combine two checks that are together necessary and sufficient.
 *   (1) Area: the summed area of all rectangles must equal the area of their
 *       overall bounding box. This fails whenever there is a net gap or overlap.
 *   (2) Corner parity: toss each rectangle's four corners into a set, toggling
 *       each (erase if already present, otherwise insert). A point touched by an
 *       even number of rectangle-corners cancels out; in a perfect tiling every
 *       interior crossing and edge T-junction is shared an even number of times,
 *       so only the four corners of the bounding box (each owned by exactly one
 *       rectangle) survive. Requiring precisely those four corners eliminates the
 *       deceptive cases where an overlap and an equal-area gap coexist — which
 *       the area test alone would accept.
 *
 * Complexity: O(n log n) time (set operations over 4n corner points) and O(n)
 *   space for the corner set.
 */

#include <vector>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        long long area = 0;                         // 64-bit: sum can reach ~8e14
        int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;
        set<pair<int, int>> corners;

        for (const auto& r : rectangles) {
            int x = r[0], y = r[1], a = r[2], b = r[3];

            // Track the overall bounding box.
            minX = min(minX, x);  minY = min(minY, y);
            maxX = max(maxX, a);  maxY = max(maxY, b);

            // Accumulate covered area (overlaps would push the sum above the box).
            area += (long long)(a - x) * (b - y);

            // Toggle the four corners: a point appearing an even number of times
            // across all rectangles cancels and should not remain in the set.
            for (const auto& p : {make_pair(x, y), make_pair(x, b),
                                   make_pair(a, y), make_pair(a, b)}) {
                auto it = corners.find(p);
                if (it != corners.end()) corners.erase(it);
                else                     corners.insert(p);
            }
        }

        // A perfect cover leaves exactly the four bounding-box corners behind.
        if (corners.size() != 4) return false;
        if (!corners.count({minX, minY}) || !corners.count({minX, maxY}) ||
            !corners.count({maxX, minY}) || !corners.count({maxX, maxY}))
            return false;

        // And the pieces must account for exactly the bounding-box area.
        long long boxArea = (long long)(maxX - minX) * (maxY - minY);
        return area == boxArea;
    }
};
