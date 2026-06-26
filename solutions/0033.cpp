/*
 * LeetCode 33 - Search in Rotated Sorted Array
 *
 * nums is an ascending array of DISTINCT integers that has possibly been rotated
 * left at some unknown pivot (e.g. [0,1,2,4,5,6,7] -> [4,5,6,7,0,1,2]). Given the
 * rotated array and a target, return the index of target, or -1 if it is absent.
 * The search must run in O(log n).
 *
 * Input  : vector<int>& nums, int target. Output : int — index of target or -1.
 *
 * Constraints: 1 <= n <= 5000; -10^4 <= nums[i], target <= 10^4; all values
 *   distinct. Values are small and unique, so no overflow and no tie handling.
 *
 * Approach: modified binary search. A rotated sorted array has the key property
 *   that for any mid, at least one of the two halves [lo..mid] and [mid..hi] is
 *   still in plain ascending order. At each step identify the sorted half by
 *   comparing nums[lo] with nums[mid]: if nums[lo] <= nums[mid] the left half is
 *   sorted, otherwise the right half is. Because that half is ordered, a simple
 *   range check tells whether target lies inside it; if so recurse into it, else
 *   recurse into the other half. Distinct values make the <= boundary checks exact.
 *
 * Complexity: O(log n) time (the search range halves each iteration); O(1) space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;       // midpoint, overflow-safe form

            if (nums[mid] == target)
                return mid;

            // Exactly one side is guaranteed sorted; find and exploit it.
            if (nums[lo] <= nums[mid]) {
                // Left half [lo..mid] is in ascending order.
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;               // target lies within the sorted left
                else
                    lo = mid + 1;               // otherwise it must be on the right
            } else {
                // Right half [mid..hi] is in ascending order.
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;               // target lies within the sorted right
                else
                    hi = mid - 1;               // otherwise it must be on the left
            }
        }

        return -1;                              // target not present
    }
};
