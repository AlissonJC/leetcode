/*
 * LeetCode 56 - Merge Intervals
 *
 * Given an array of intervals where intervals[i] = [start_i, end_i], merge all
 * overlapping intervals and return an array of the non-overlapping intervals
 * that together cover exactly the same points as the input. Intervals that only
 * touch at an endpoint (for example [1, 4] and [4, 5]) are considered
 * overlapping and merge into one ([1, 5]).
 *
 * Input  : vector<vector<int>> intervals - a list of closed [start, end] pairs.
 * Output : vector<vector<int>> - the merged, pairwise-disjoint intervals.
 *
 * Constraints: 1 <= intervals.length <= 10^4; intervals[i].length == 2;
 *   0 <= start_i <= end_i <= 10^4.
 *
 * Approach: sort the intervals by start, then sweep once. Once sorted, any
 *   interval that overlaps an earlier one is adjacent to the block it belongs
 *   to, so maintain a current merged block: if the next interval starts at or
 *   before the block's current end, it overlaps (or touches) and the block's end
 *   is stretched to the larger of the two ends; otherwise the block is complete,
 *   so emit it and begin a fresh block at the next interval. Using start <= end
 *   (inclusive) is exactly what lets touching intervals fuse.
 *
 * Complexity: O(n log n) time, dominated by the sort (the sweep is O(n)); O(n)
 *   space for the output (O(1) auxiliary beyond it). Coordinates are <= 10^4,
 *   so plain int cannot overflow.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Sort by start; ties on start are harmless since merging takes the max
        // end regardless of which equal-start interval comes first.
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        vector<vector<int>> merged;
        for (const auto& iv : intervals) {
            // Overlap or touch with the open block iff this start does not exceed
            // that block's end. Extend the block's end; else open a new block.
            if (!merged.empty() && iv[0] <= merged.back()[1]) {
                merged.back()[1] = max(merged.back()[1], iv[1]);
            } else {
                merged.push_back(iv);
            }
        }
        return merged;
    }
};
