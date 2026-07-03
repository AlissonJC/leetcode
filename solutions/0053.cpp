/*
 * LeetCode 53 - Maximum Subarray
 *
 * Given an integer array nums, find the contiguous subarray (containing at
 * least one element) that has the largest sum, and return that sum.
 *
 * Input  : vector<int> nums - the array to search.
 * Output : int - the maximum sum over all non-empty contiguous subarrays.
 *
 * Constraints: 1 <= n == nums.length <= 10^5; -10^4 <= nums[i] <= 10^4.
 *
 * Approach: Kadane's algorithm - a single left-to-right sweep. Maintain `best
 *   ending here`, the largest sum of a subarray that ends exactly at the current
 *   index. Extending it by one element is only worthwhile if the run so far is
 *   positive; the instant it turns negative it can only drag a future subarray
 *   down, so drop it and start fresh at the current element. Concretely,
 *   curEnd = max(nums[i], curEnd + nums[i]). The answer is the maximum of these
 *   per-position values, tracked in `best`. Seeding both with nums[0] (rather
 *   than 0) is what makes an all-negative array return its least-negative single
 *   element instead of a spurious 0.
 *
 *   (The divide-and-conquer follow-up - split, recurse on halves, and combine
 *   with the best subarray straddling the midpoint - also solves it but in
 *   O(n log n); Kadane's linear scan is strictly better.)
 *
 * Complexity: O(n) time - one pass; O(1) extra space - two running integers.
 *   The sum never overflows int: |answer| <= n * max|nums[i]| = 10^5 * 10^4 =
 *   10^9, comfortably below 2^31 - 1.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // Seed with the first element so a non-empty subarray is always chosen,
        // even when every value is negative.
        int best = nums[0];     // best sum found over any subarray so far
        int curEnd = nums[0];   // best sum of a subarray ending at the current index

        for (int i = 1; i < (int)nums.size(); ++i) {
            // Either extend the running subarray, or abandon it and restart at
            // nums[i] - whichever yields the larger sum ending here.
            curEnd = max(nums[i], curEnd + nums[i]);
            best = max(best, curEnd);
        }

        return best;
    }
};
