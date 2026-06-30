/*
 * LeetCode 3759 - Count Elements With at Least K Greater Values
 *
 * Given an integer array nums of length n and an integer k, an element is "qualified"
 * if at least k other elements of the array are strictly greater than it. Return how
 * many elements are qualified.
 *
 * Input  : vector<int> nums; int k. Output : int — number of qualified elements.
 *
 * Constraints: 1 <= n <= 1e5; 1 <= nums[i] <= 1e9; 0 <= k < n. Counts fit in a 32-bit
 *   int (at most n elements), and only comparisons are done, so no wider type is needed.
 *
 * Approach: sort ascending. After sorting, the number of elements strictly greater than
 *   a value v is n minus the count of elements <= v, i.e. n - upper_bound(v). An element
 *   is qualified exactly when that count is >= k. Walk the array from the largest value
 *   down: the elements strictly greater than the current value are everything past the
 *   block of values equal to it, so a single right-to-left scan that tracks the start of
 *   the current equal block gives each element's "strictly greater" count in O(1).
 *
 * Complexity: O(n log n) time (the sort dominates the linear scan); O(1) extra space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        int n = (int)nums.size();
        sort(nums.begin(), nums.end());

        int qualified = 0;
        // Scan right to left. `greater` = number of elements strictly larger than the
        // current value; it only changes when the value changes (ties share a count).
        int i = n - 1;
        while (i >= 0) {
            int greater = n - 1 - i;            // elements to the right are all > nums[i]
            // Extend over the whole block of equal values; they all see the same `greater`.
            int j = i;
            while (j >= 0 && nums[j] == nums[i]) --j;
            int blockSize = i - j;              // how many elements equal nums[i]
            if (greater >= k) qualified += blockSize;
            i = j;                              // jump to the next smaller value
        }
        return qualified;
    }
};
