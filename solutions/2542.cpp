/*
 * LeetCode 2542 - Maximum Subsequence Score
 *
 * Given two 0-indexed integer arrays nums1 and nums2 of equal length n and an integer k,
 * choose exactly k indices. The score is (sum of the chosen nums1 values) multiplied by
 * (the minimum of the chosen nums2 values). Return the maximum possible score.
 *
 * Input  : vector<int> nums1, vector<int> nums2 (length n), int k.
 * Output : long long — the maximum achievable score over all size-k index subsets.
 *
 * Constraints: 1 <= n <= 1e5, 0 <= nums1[i], nums2[j] <= 1e5, 1 <= k <= n.
 *
 * Approach: Fix which chosen element supplies the minimum nums2. Sort the (nums2, nums1)
 *   pairs by nums2 DESCENDING and sweep; the current pair's nums2 is the smallest processed
 *   so far, so treat it as the group minimum. Among all pairs seen (all with nums2 >= the
 *   current one), the best partners are the k with the LARGEST nums1, so maintain a min-heap
 *   of nums1 values that evicts its smallest once the heap exceeds size k, tracking the sum
 *   of what it holds. Whenever the heap holds exactly k, sum * currentNums2 is a candidate;
 *   keep the maximum. (Even when the current element is itself evicted, sum * currentNums2
 *   never exceeds that heap group's true score, and the true optimum is hit at the iteration
 *   whose nums2 is the optimal group's minimum — so the max over all iterations is exact.)
 *
 * Overflow: sum of k nums1 reaches k * 1e5 <= 1e10 and the score reaches ~1e15, so sum, the
 *   score, and the answer are all 64-bit.
 *
 * Complexity: O(n log n) time (sort + heap), O(n) space.
 */

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = (int)nums1.size();

        // Pair each index as (nums2, nums1) and sort by nums2 descending.
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = {nums2[i], nums1[i]};
        sort(a.begin(), a.end(), greater<>());        // largest nums2 first

        priority_queue<int, vector<int>, greater<int>> minHeap;  // smallest nums1 on top
        long long sum = 0, ans = 0;

        for (const auto& [n2, n1] : a) {
            minHeap.push(n1);                          // consider this element's nums1
            sum += n1;
            if ((int)minHeap.size() > k) {             // keep only the k largest nums1
                sum -= minHeap.top();                  // drop the smallest
                minHeap.pop();
            }
            if ((int)minHeap.size() == k)              // n2 is the group's minimum (sorted desc)
                ans = max(ans, sum * (long long)n2);
        }
        return ans;
    }
};
