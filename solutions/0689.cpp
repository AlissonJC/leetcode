/*
 * LeetCode 689 - Maximum Sum of 3 Non-Overlapping Subarrays
 *
 * Given an integer array nums and an integer k, pick three non-overlapping subarrays,
 * each of length exactly k, whose combined sum is maximum. Return the three starting
 * indices (0-indexed, in increasing order). Among all maximum-sum choices, return the
 * lexicographically smallest triple of indices.
 *
 * Input  : vector<int> nums, int k.
 * Output : vector<int> of three starting indices {l, mid, r}.
 *
 * Constraints: 1 <= n <= 2e4, 1 <= nums[i] < 2^16, 1 <= k <= floor(n/3).
 *
 * Approach: Reduce to windows. Let w[i] be the sum of the length-k subarray starting at
 *   i, for i in [0, m-1] where m = n-k+1; compute all w[i] with a sliding window. Fix the
 *   MIDDLE window at index mid: the best left window must lie in [0, mid-k] and the best
 *   right window in [mid+k, m-1], and those two choices are independent of each other.
 *   Precompute:
 *     left[i]  = index of the largest w in [0..i]      (earliest index on ties)
 *     right[i] = index of the largest w in [i..m-1]    (earliest index on ties)
 *   Then sweep mid over its valid range and keep the triple (left[mid-k], mid, right[mid+k])
 *   with the largest total.
 *
 *   Lexicographic tie-break: build left[] with strict '>' and right[] with '>=' so each
 *   keeps the SMALLEST index among equal-sum windows, and update the answer only on a
 *   STRICTLY greater total so the smallest qualifying mid wins. Because left[] as an index
 *   is non-decreasing in i (it only ever jumps forward to the new position), the candidate
 *   left index is non-decreasing in mid; hence the smallest optimal mid also yields the
 *   smallest l, and l is compared first — so the swept winner is the lexicographically
 *   smallest optimal triple.
 *
 * Complexity: O(n) time (three linear passes), O(n) space for the window/left/right arrays.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = (int)nums.size();
        int m = n - k + 1;                          // count of length-k windows: indices [0, m-1]

        // w[i] = sum of nums[i..i+k-1], maintained by a sliding window.
        vector<long long> w(m, 0);
        long long s = 0;
        for (int i = 0; i < k; ++i) s += nums[i];   // first window
        w[0] = s;
        for (int i = 1; i < m; ++i) {               // slide: drop nums[i-1], add nums[i+k-1]
            s += (long long)nums[i + k - 1] - nums[i - 1];
            w[i] = s;
        }

        // left[i]: best window index in [0..i]; strict '>' => keep the earliest on ties.
        vector<int> left(m);
        left[0] = 0;
        for (int i = 1; i < m; ++i)
            left[i] = (w[i] > w[left[i - 1]]) ? i : left[i - 1];

        // right[i]: best window index in [i..m-1]; '>=' => keep the earliest (current) on ties.
        vector<int> right(m);
        right[m - 1] = m - 1;
        for (int i = m - 2; i >= 0; --i)
            right[i] = (w[i] >= w[right[i + 1]]) ? i : right[i + 1];

        // Fix the middle window; left/right are then forced to their best legal picks.
        vector<int> ans = {-1, -1, -1};
        long long best = -1;
        for (int mid = k; mid <= m - 1 - k; ++mid) {         // needs mid-k >= 0 and mid+k <= m-1
            int l = left[mid - k];
            int r = right[mid + k];
            long long total = w[l] + w[mid] + w[r];
            if (total > best) {                              // strict '>' -> smallest mid (lex smallest)
                best = total;
                ans = {l, mid, r};
            }
        }
        return ans;
    }
};
