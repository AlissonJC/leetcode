/*
 * LeetCode 57 - Insert Interval
 *
 * You are given a list of non-overlapping intervals sorted in ascending order
 * by start, plus one new interval. Insert the new interval so that the list
 * stays sorted and non-overlapping, merging with any intervals it overlaps or
 * touches, and return the resulting list.
 *
 * Input  : vector<vector<int>> intervals - disjoint [start, end] pairs sorted
 *          by start; vector<int> newInterval - the [start, end] to insert.
 * Output : vector<vector<int>> - the updated sorted, non-overlapping list.
 *
 * Constraints: 0 <= intervals.length <= 10^4 (may be empty); intervals[i] has
 *   length 2; 0 <= start_i <= end_i <= 10^5; intervals is sorted by start and
 *   non-overlapping; newInterval is a valid [start, end] with the same bounds.
 *
 * Approach: since the existing intervals are already sorted and disjoint, one
 *   linear pass in three phases inserts the new interval without any re-sorting.
 *   Phase 1 copies every interval that lies entirely to the LEFT of the new one
 *   (its end is strictly before the new start). Phase 2 absorbs every interval
 *   that overlaps or touches the new one - each such interval has start <= the
 *   new (growing) end - expanding the new interval to the minimum start and
 *   maximum end seen, then emits that single merged interval. Phase 3 copies the
 *   remaining intervals, all lying entirely to the RIGHT. Testing "end < start"
 *   (strict) for phase 1 versus "start <= end" (inclusive) for phase 2 is what
 *   makes intervals that merely touch at an endpoint merge.
 *
 * Complexity: O(n) time - a single pass over the intervals; O(n) space for the
 *   output. Coordinates are <= 10^5, so int cannot overflow.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int n = (int)intervals.size();
        int i = 0;

        // Grow these bounds as the new interval swallows overlapping neighbors.
        int lo = newInterval[0], hi = newInterval[1];

        // Phase 1: intervals ending strictly before the new start - untouched.
        while (i < n && intervals[i][1] < lo) {
            res.push_back(intervals[i]);
            ++i;
        }

        // Phase 2: every interval starting at or before the current end overlaps
        // (or touches) the new interval; fold it in by widening [lo, hi].
        while (i < n && intervals[i][0] <= hi) {
            lo = min(lo, intervals[i][0]);
            hi = max(hi, intervals[i][1]);
            ++i;
        }
        res.push_back({lo, hi});   // emit the (possibly merged) new interval once

        // Phase 3: intervals starting after the merged interval ends - untouched.
        while (i < n) {
            res.push_back(intervals[i]);
            ++i;
        }

        return res;
    }
};
