/*
 * LeetCode 986 - Interval List Intersections
 *
 * Given two lists of closed intervals, firstList and secondList, where each list
 * is pairwise disjoint and already sorted by start, return the intersection of the
 * two lists: every interval that lies inside an interval of firstList AND inside an
 * interval of secondList. Two closed intervals [a, b] and [c, d] overlap exactly
 * when max(a, c) <= min(b, d), and their intersection is then [max(a, c), min(b, d)]
 * (a single point such as [5, 5] is a valid closed interval and must be reported).
 *
 * Input  : vector<vector<int>> firstList, secondList (each entry is {start, end}).
 * Output : vector<vector<int>> — the intersections, in sorted order.
 *
 * Constraints: 0 <= firstList.length, secondList.length <= 1000; the total length
 *   is at least 1; 0 <= start < end <= 1e9; intervals within a list are disjoint and
 *   sorted (end_i < start_{i+1}). Endpoints reach 1e9 but the result only ever copies
 *   existing endpoints via max/min, so no arithmetic and no overflow — int suffices.
 *
 * Approach: merge with two pointers i and j walking the two already-sorted lists.
 *   For the current pair compute the overlap [lo, hi] = [max of starts, min of ends];
 *   if lo <= hi it is a real intersection, so emit it. Then advance the interval that
 *   finishes first (smaller end): it can never intersect anything later in the other
 *   list, while the one with the larger end may still overlap the other list's next
 *   interval. Because each list is internally disjoint, every pair is examined at most
 *   once and no intersection is missed.
 *
 * Complexity: O(n + m) time (each step advances one pointer); O(1) extra space
 *   beyond the returned answer.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList,
                                             vector<vector<int>>& secondList) {
        vector<vector<int>> result;
        int i = 0, j = 0;
        int n = (int)firstList.size(), m = (int)secondList.size();

        // Walk both lists together; if either is empty the loop never runs and the
        // answer is empty, which is exactly what an empty input should produce.
        while (i < n && j < m) {
            // Overlap of the two current intervals: starts no earlier than the later
            // start, ends no later than the earlier end.
            int lo = max(firstList[i][0], secondList[j][0]);
            int hi = min(firstList[i][1], secondList[j][1]);

            // lo == hi is a valid one-point intersection (e.g. [5, 5]), so the test
            // is "<=", not "<".
            if (lo <= hi)
                result.push_back({lo, hi});

            // Drop whichever interval ends first; it cannot meet any later interval
            // of the other list. On a tie either choice is correct.
            if (firstList[i][1] < secondList[j][1])
                ++i;
            else
                ++j;
        }

        return result;
    }
};
