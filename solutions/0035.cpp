/*
 * LeetCode 35 - Search Insert Position
 *
 * Given a sorted array of distinct integers and a target, return the index of
 * the target if present, otherwise the index where it would be inserted to keep
 * the array sorted. Must run in O(log n).
 *
 * Input  : sorted vector<int> nums (distinct, ascending), int target.
 * Output : the target's index, or its insertion index.
 * Constraints: 1 <= nums.length <= 1e4, -1e4 <= nums[i], target <= 1e4.
 *
 * Approach: the answer is the first index i with nums[i] >= target (a lower
 *   bound) -- if target exists that is its index, otherwise it is exactly where
 *   it would slot in. Binary search the half-open range [0, n]: keep the
 *   invariant that the answer lies in [lo, hi]; narrow by comparing the middle
 *   value to target until the range collapses.
 *
 * Complexity: O(log n) time, O(1) space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size();        // answer is somewhere in [lo, hi]
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < target) lo = mid + 1;  // target must go strictly after mid
            else hi = mid;                         // mid is a candidate, keep it in range
        }
        return lo;                                 // first index with nums[i] >= target
    }
};
