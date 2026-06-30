/*
 * LeetCode 1851 - Minimum Interval to Include Each Query
 *
 * Each intervals[i] = [left, right] is an inclusive range whose "size" is the
 * number of integers it contains, right - left + 1. For every value queries[j],
 * report the size of the SMALLEST interval that contains it (left <= q <= right),
 * or -1 when no interval covers it. Answers must be returned in the original query
 * order.
 *
 * Input  : vector<vector<int>> intervals ({left, right}); vector<int> queries.
 * Output : vector<int> — for each query, the minimum covering interval size or -1.
 *
 * Constraints: 1 <= intervals.length, queries.length <= 1e5; 1 <= left <= right <= 1e7;
 *   1 <= queries[j] <= 1e7. A size is at most 1e7, so plain int never overflows.
 *   A naive "scan all intervals per query" is up to 1e10 operations and would TLE,
 *   so the queries are processed offline in sorted order instead.
 *
 * Approach: answer the queries offline. Sort intervals by left endpoint and sort the
 *   queries ascending (remembering each query's original index). Sweep the queries in
 *   increasing order while keeping a min-heap keyed by interval size, each entry being
 *   {size, right}. Before answering query q:
 *     1. push every interval whose left <= q (a pointer advances monotonically, so each
 *        interval is added exactly once);
 *     2. pop every heap top whose right < q — such an interval cannot contain q, and
 *        because q only grows it can never contain any later query either, so removing
 *        it permanently is safe.
 *   Whatever remains on top is the smallest-size interval still covering q; an empty
 *   heap means the answer is -1. Each result is stored at its original index.
 *
 * Complexity: O(N log N + Q log Q + (N + Q) log N) time — every interval is pushed and
 *   popped at most once; O(N + Q) space for the heap and the answer array.
 */

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = (int)intervals.size();
        int q = (int)queries.size();

        // Process intervals from the smallest left endpoint upward.
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        // Sort query indices by query value so we can sweep queries in increasing order
        // while still writing each answer back to its original position.
        vector<int> order(q);
        for (int i = 0; i < q; ++i) order[i] = i;
        sort(order.begin(), order.end(),
             [&](int a, int b) { return queries[a] < queries[b]; });

        // Min-heap of {size, right}: the smallest currently-valid interval sits on top.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> ans(q);
        int ptr = 0;  // next interval not yet pushed; advances monotonically

        for (int idx : order) {
            int cur = queries[idx];

            // Add every interval that starts at or before the current query value.
            while (ptr < n && intervals[ptr][0] <= cur) {
                int size = intervals[ptr][1] - intervals[ptr][0] + 1;
                pq.push({size, intervals[ptr][1]});
                ++ptr;
            }

            // Drop intervals that end before the query: they cannot contain it, and
            // since queries only increase they are useless from now on.
            while (!pq.empty() && pq.top().second < cur)
                pq.pop();

            // The remaining top is the smallest covering interval; empty heap => -1.
            ans[idx] = pq.empty() ? -1 : pq.top().first;
        }

        return ans;
    }
};
