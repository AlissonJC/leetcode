/*
 * LeetCode 34 - Find First and Last Position of Element in Sorted Array
 *
 * Given nums sorted in non-decreasing order and a target, return the indices of
 * the first and last occurrence of target as {first, last}. If target is absent,
 * return {-1, -1}. The algorithm must run in O(log n).
 *
 * Input  : vector<int>& nums, int target. Output : vector<int> {first, last}.
 *
 * Constraints: 0 <= n <= 10^5; -10^9 <= nums[i], target <= 10^9; nums is
 *   non-decreasing. Values fit in 32-bit int; the array may be empty.
 *
 * Approach: two boundary binary searches (this is exactly std::lower_bound /
 *   std::upper_bound, written out to show the leftmost/rightmost logic).
 *     - lower bound: the first index whose value is >= target. If that index is
 *       out of range or its value isn't target, target does not occur -> {-1,-1}.
 *     - upper bound: the first index whose value is > target. The last occurrence
 *       is one position before it.
 *   Each search keeps a half-open range [lo, hi) and moves lo or hi past mid based
 *   on the comparison, converging on the boundary in O(log n). Doing an "> target"
 *   search directly (rather than reusing the >= search on target+1) avoids any
 *   concern about target+1 at the top of the value range.
 *
 * Complexity: O(log n) time (two binary searches); O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = lowerBound(nums, target);

        // If no value reaches target, or the value there isn't target, it's absent.
        if (first == (int)nums.size() || nums[first] != target)
            return {-1, -1};

        // upperBound is the first index strictly greater than target, so the last
        // occurrence sits immediately before it. Since `first` matched, this index
        // is at least first + 1, so subtracting one stays in range.
        int last = upperBound(nums, target) - 1;
        return {first, last};
    }

private:
    // First index in [0, n] whose value is >= target (std::lower_bound).
    int lowerBound(const vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size();          // half-open range [lo, hi)
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < target)
                lo = mid + 1;                       // mid too small; boundary is right
            else
                hi = mid;                           // mid qualifies; boundary is here or left
        }
        return lo;
    }

    // First index in [0, n] whose value is > target (std::upper_bound).
    int upperBound(const vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] <= target)
                lo = mid + 1;                       // still <= target; boundary is right
            else
                hi = mid;                           // first value > target seen; here or left
        }
        return lo;
    }
};
