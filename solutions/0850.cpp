/*
 * LeetCode 850 - Rectangle Area II
 *
 * Given axis-aligned rectangles as [x1, y1, x2, y2] (bottom-left and top-right
 * corners), compute the area of their union — region covered by two or more
 * rectangles is counted only once. The result can be huge, so return it modulo
 * 1e9 + 7.
 *
 * Input  : vector<vector<int>> rectangles. Output : int — union area mod 1e9+7.
 *
 * Constraints: 1 <= rectangles.length <= 200; coordinates in [0, 1e9];
 *   x1 <= x2, y1 <= y2; every rectangle has non-zero area.
 *
 * Approach: coordinate-compress the x axis, then sweep vertical strips. Sorting
 *   the distinct x-coordinates splits the plane into strips [x_i, x_{i+1}); within
 *   one strip every rectangle either fully spans it or does not touch it, so the
 *   covered shape in that strip is just the union of the y-intervals of the
 *   spanning rectangles. For each strip, gather those y-intervals, merge them
 *   with a one-pass sweep to get the covered height, and add width * height to a
 *   running total. Crucially, the union area is at most the bounding box
 *   1e9 * 1e9 = 1e18, which fits in a signed 64-bit integer, so accumulate the
 *   exact area and take the modulus only once at the very end — taking it earlier
 *   would corrupt the width * height geometry.
 *
 * Complexity: O(R^2 log R) time — O(R) strips, each sorting up to O(R) intervals
 *   (R = number of rectangles, <= 200). O(R) extra space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        const long long MOD = 1000000007LL;

        // Compress the x axis: the strip boundaries are exactly the distinct x's.
        vector<long long> xs;
        for (const auto& r : rectangles) {
            xs.push_back(r[0]);
            xs.push_back(r[2]);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        long long total = 0;  // exact union area; <= 1e18, so no overflow

        // Sweep each vertical strip [xs[i], xs[i+1]).
        for (size_t i = 0; i + 1 < xs.size(); ++i) {
            long long left = xs[i], right = xs[i + 1];
            long long width = right - left;

            // Collect the y-spans of rectangles that fully cover this strip.
            vector<pair<long long, long long>> ys;
            for (const auto& r : rectangles) {
                if (r[0] <= left && r[2] >= right)
                    ys.emplace_back(r[1], r[3]);
            }
            sort(ys.begin(), ys.end());

            // Merge the y-intervals in one pass to get the covered height.
            long long covered = 0, curLo = 0, curHi = 0;
            bool open = false;
            for (const auto& seg : ys) {
                if (!open) {                       // first interval starts a run
                    curLo = seg.first; curHi = seg.second; open = true;
                } else if (seg.first <= curHi) {   // overlaps/touches the run: extend
                    curHi = max(curHi, seg.second);
                } else {                           // gap: close the run, start a new one
                    covered += curHi - curLo;
                    curLo = seg.first; curHi = seg.second;
                }
            }
            if (open) covered += curHi - curLo;    // flush the final run

            total += width * covered;              // partial sum stays <= 1e18
        }

        return static_cast<int>(total % MOD);      // single modulus at the end
    }
};
