/*
 * LeetCode 26 - Remove Duplicates from Sorted Array
 *
 * Given a non-decreasing array nums, remove duplicates in place so that each
 * unique value appears once, keeping the relative order. Return k, the number of
 * unique values; the first k entries of nums must hold those values in order.
 *
 * Input  : vector<int>& nums (sorted non-decreasing), modified in place.
 * Output : int k = number of unique values, with nums[0..k-1] the unique values.
 * Constraints: 1 <= nums.length <= 3e4, -100 <= nums[i] <= 100.
 *
 * Approach: two pointers. k is the count of unique values written so far (and the
 *   next write position). Since the array is sorted, a value is new exactly when
 *   it differs from the last unique one, nums[k-1]; in that case write it to
 *   nums[k] and advance k. Start k at 1 because the first element is always
 *   unique.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 0) return 0;                 // guard (constraints give n >= 1)
        int k = 1;                            // nums[0] is always kept
        for (int i = 1; i < n; ++i) {
            if (nums[i] != nums[k - 1]) {     // a value not seen yet
                nums[k] = nums[i];
                ++k;
            }
        }
        return k;
    }
};
