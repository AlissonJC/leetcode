/*
 * LeetCode 327 - Count of Range Sum
 *
 * Count the subarrays whose element sum lies in [lower, upper] (inclusive). The sum of
 * nums[i..j] (i <= j) is a "range sum"; report how many of the O(n^2) range sums fall in
 * the given band.
 *
 * Input  : vector<int> nums, int lower, int upper.
 * Output : the count of range sums within [lower, upper].
 *
 * Constraints: 1 <= n <= 1e5; -2^31 <= nums[i] <= 2^31 - 1; -1e5 <= lower <= upper <= 1e5;
 *   the answer fits in a 32-bit integer.
 *
 * Approach: with prefix sums P (P[0]=0, P[k]=nums[0]+...+nums[k-1]), a range sum equals
 *   P[b] - P[a] for some 0 <= a < b <= n. So the task becomes: count index pairs a < b with
 *   lower <= P[b] - P[a] <= upper. Merge sort the prefix array; when merging two halves that
 *   are individually sorted, every left index is < every right index, so each cross pair is a
 *   valid (a, b). For each left value x = P[a], the matching right values are those in
 *   [x+lower, x+upper]; because both halves are sorted, two monotone pointers sweep that
 *   window as x increases, counting in O(size) before the ordinary merge. Summing the cross
 *   counts across all merges gives the answer.
 *
 * Overflow note: prefix sums can reach ~1e5 * 2^31 ~ 2e14, so P and the window bounds use
 *   64-bit integers; the running count is kept 64-bit too and cast down at the end (the
 *   final value is promised to fit in int).
 *
 * Complexity: O(n log n) time, O(n) space for the prefix and merge buffers.
 */

#include <vector>
using namespace std;

class Solution {
    long long lo, hi;          // the [lower, upper] band as 64-bit
    vector<long long> P;       // prefix sums, size n+1
    vector<long long> buf;     // merge scratch

    long long sortCount(int l, int r) {   // count valid cross pairs in P[l..r]; sort P[l..r]
        if (l >= r)
            return 0;                      // single prefix value: no pair
        int mid = l + (r - l) / 2;
        long long count = sortCount(l, mid) + sortCount(mid + 1, r);

        // Count pairs a in [l, mid], b in [mid+1, r] with P[b] - P[a] in [lo, hi].
        int jLow = mid + 1, jHigh = mid + 1;
        for (int a = l; a <= mid; ++a) {
            // First right value >= P[a] + lo, and first > P[a] + hi.
            while (jLow <= r && P[jLow] < P[a] + lo) ++jLow;
            while (jHigh <= r && P[jHigh] <= P[a] + hi) ++jHigh;
            count += jHigh - jLow;
        }

        // Standard merge of the two sorted halves.
        int i = l, j = mid + 1, t = l;
        while (i <= mid && j <= r)
            buf[t++] = (P[i] <= P[j]) ? P[i++] : P[j++];
        while (i <= mid) buf[t++] = P[i++];
        while (j <= r)   buf[t++] = P[j++];
        for (int k = l; k <= r; ++k)
            P[k] = buf[k];

        return count;
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = (int)nums.size();
        lo = lower; hi = upper;
        P.assign(n + 1, 0);
        for (int i = 0; i < n; ++i)
            P[i + 1] = P[i] + nums[i];     // long long accumulation avoids overflow
        buf.resize(n + 1);
        return (int)sortCount(0, n);
    }
};
