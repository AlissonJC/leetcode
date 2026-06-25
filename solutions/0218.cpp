/*
 * LeetCode 218 - The Skyline Problem
 *
 * Each building is an axis-aligned rectangle grounded at height 0, given as
 * [left, right, height]. Return the skyline — the outer contour formed by all
 * buildings — as a list of "key points" [x, y] sorted by x. Each key point is
 * the left end of a horizontal segment at height y; the final key point has
 * y = 0 to close the contour at the rightmost edge. No two consecutive segments
 * may share the same height (collinear pieces must be merged).
 *
 * Input  : vector<vector<int>> buildings. Output : the key points of the skyline.
 *
 * Constraints: 1 <= n <= 1e4; 0 <= left < right <= 2^31 - 1; 1 <= height <=
 *   2^31 - 1. Every value (including a negated start height, which is >= INT_MIN)
 *   fits in a 32-bit int.
 *
 * Approach: a left-to-right sweep over building edges. Convert each building into
 *   two events: a start at x = left and an end at x = right. Maintain a multiset
 *   of heights currently "covering" the sweep position, seeded with the ground
 *   height 0. A start inserts its height; an end removes one copy of its height.
 *   After each event the tallest active height is the skyline level there, so
 *   whenever that maximum changes the current x with the new maximum is a key
 *   point. Event order at a shared x is what makes this correct: encode a start
 *   as -height and an end as +height and sort by (x, signedHeight). Then starts
 *   come before ends, taller starts before shorter ones, and shorter ends before
 *   taller ones — which avoids emitting a false point where one building begins
 *   exactly where another (of the same height) ends.
 *
 * Complexity: O(n log n) time — sorting 2n events plus O(log n) multiset updates
 *   each — and O(n) space for the events and the active-height multiset.
 */

#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // Each building yields a start (-height) and an end (+height) event.
        vector<pair<int, int>> events;
        events.reserve(buildings.size() * 2);
        for (const auto& b : buildings) {
            events.push_back({b[0], -b[2]});   // start: negative height
            events.push_back({b[1],  b[2]});   // end:   positive height
        }
        // Sorting by (x, signedHeight) gives the exact tie-breaking we need:
        // at equal x, starts precede ends, taller starts first, shorter ends first.
        sort(events.begin(), events.end());

        vector<vector<int>> result;
        multiset<int> active;                  // active heights; ground 0 is always present
        active.insert(0);
        int prevMax = 0;

        for (const auto& [x, h] : events) {
            if (h < 0)
                active.insert(-h);             // a building starts here
            else
                active.erase(active.find(h));  // a building ends: drop exactly ONE copy

            int curMax = *active.rbegin();     // tallest active height = skyline level
            if (curMax != prevMax) {           // the contour height changed -> key point
                result.push_back({x, curMax});
                prevMax = curMax;
            }
        }

        return result;
    }
};
