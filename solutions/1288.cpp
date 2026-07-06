/*
 * LeetCode 1288 - Remove Covered Intervals
 *
 * Given a list of half-open intervals intervals[i] = [l_i, r_i), remove every interval
 * that is covered by another interval in the list, and return how many intervals remain.
 * Interval [a, b) is covered by [c, d) exactly when c <= a and b <= d.
 *
 * Input  : vector<vector<int>>& intervals, each a 2-element {l, r} with l < r.
 * Output : int -- the count of intervals not covered by any other interval.
 *
 * Constraints: 1 <= n <= 1000; 0 <= l_i < r_i <= 1e5; all intervals are unique.
 *
 * Approach: sort by left endpoint ascending, breaking ties by right endpoint
 *   DESCENDING, then sweep left to right keeping maxR, the largest right endpoint seen
 *   so far. After sorting, any earlier interval has a left endpoint <= the current one,
 *   so the current interval [l, r) is covered iff r <= maxR (that earlier interval also
 *   extends at least as far right). If r > maxR it is not covered: count it and raise
 *   maxR to r. The descending tie-break matters: when two intervals share a left
 *   endpoint, the wider one must be processed first so the narrower one is recognized
 *   as covered rather than mistakenly counted.
 *
 * Complexity: O(n log n) time dominated by the sort, O(1) extra space (in-place sort
 *   plus a couple of counters). Endpoints fit in int (<= 1e5).
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Left ascending; on equal left, right descending so the widest comes first.
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] != b[0]) return a[0] < b[0];
                 return a[1] > b[1];
             });

        int remaining = 0;
        int maxR = 0;                        // largest right endpoint kept so far (r >= 1)
        for (const auto& iv : intervals) {
            if (iv[1] > maxR) {              // extends beyond everything before -> not covered
                ++remaining;
                maxR = iv[1];
            }
            // else iv[1] <= maxR: some earlier interval (left <= iv[0]) covers it -> drop.
        }
        return remaining;
    }
};
