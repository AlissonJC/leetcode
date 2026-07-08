/*
 * LeetCode 81 - Search in Rotated Sorted Array II
 *
 * An integer array sorted in non-decreasing order (duplicates allowed) is rotated at
 * an unknown pivot, e.g. [1,2,3,3,4] -> [3,4,1,2,3]. Given the rotated array nums and
 * a target, return true if target appears in nums, false otherwise, doing as few
 * operations as possible.
 *
 * Input  : vector<int>& nums (rotated, may contain duplicates), int target.
 * Output : bool — whether target is present.
 *
 * Constraints: 1 <= n <= 5000, -1e4 <= nums[i], target <= 1e4.
 *
 * Approach: Binary search adapted for rotation. At each step, with window [lo, hi] and
 *   mid in the middle:
 *     - If nums[mid] == target, done.
 *     - If nums[lo] == nums[mid] == nums[hi], we cannot tell which half is sorted (the
 *       ends look identical), so shrink the window from both sides (lo++, hi--). This is
 *       the ONLY case duplicates add over the distinct-value version, and it is exactly
 *       what makes the worst case O(n): all-equal array with target absent forces this
 *       branch every time. When the three are NOT all equal, nums[lo] == nums[mid] can
 *       only happen if the left half is genuinely sorted, so the tests below are safe.
 *     - Else if nums[lo] <= nums[mid], the LEFT half [lo..mid] is sorted: go left when
 *       target lies in [nums[lo], nums[mid]), otherwise go right.
 *     - Else the RIGHT half [mid..hi] is sorted: go right when target lies in
 *       (nums[mid], nums[hi]], otherwise go left.
 *
 *   Why "sorted half" reasoning holds: a rotated non-decreasing array has at most one
 *   drop, and every element before it is >= every element after it. If nums[lo] < nums[mid]
 *   no drop can sit in [lo..mid], so that half is sorted; the equal case is only unsafe
 *   when nums[hi] also matches, which the triple-equal guard already peels off.
 *
 * Complexity: O(log n) average, O(n) worst case (many duplicates); O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;          // avoids lo+hi overflow (harmless here, but a good habit)
            if (nums[mid] == target) return true;

            // Ambiguous ends: can't identify the sorted half, so trim both by one.
            if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
                ++lo;
                --hi;
            } else if (nums[lo] <= nums[mid]) {    // left half [lo..mid] is sorted
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;                  // target within the sorted left half
                else
                    lo = mid + 1;                  // otherwise it can only be on the right
            } else {                               // right half [mid..hi] is sorted
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;                  // target within the sorted right half
                else
                    hi = mid - 1;                  // otherwise it can only be on the left
            }
        }
        return false;                              // window exhausted, target never matched
    }
};
