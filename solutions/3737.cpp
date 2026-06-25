/*
 * LeetCode 3737 - Count Subarrays With Majority Element I
 *
 * Count the subarrays of nums in which `target` is the majority element -- i.e.
 * it appears strictly more than half the times of that subarray.
 *
 * Input  : vector<int> nums, int target.   Output: the number of such subarrays.
 * Constraints: 1 <= nums.length <= 1000, 1 <= nums[i], target <= 1e9.
 *
 * Approach: target is the majority of a subarray of length L iff
 *   count(target) > L/2, i.e. 2*count(target) - L > 0. Map each element to +1
 *   when it equals target and -1 otherwise; then for any subarray that running
 *   value equals 2*count(target) - L, so target is the majority exactly when the
 *   subarray's mapped sum is positive (a positive sum also forces count >= 1, so
 *   target really occurs). With n <= 1000, enumerate every start and extend to
 *   the right, accumulating the sum and counting whenever it is > 0.
 *
 * Complexity: O(n^2) time, O(1) extra space (~5e5 steps for n = 1000).
 */

#include <vector>
using namespace std;

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = (int)nums.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int sum = 0;                                  // 2*count(target) - length so far
            for (int j = i; j < n; ++j) {
                sum += (nums[j] == target) ? 1 : -1;
                if (sum > 0) ++ans;                       // target is the majority of nums[i..j]
            }
        }
        return ans;                                       // <= n(n+1)/2 ~ 5e5, fits in int
    }
};
