/*
 * LeetCode 2161 - Partition Array According to Given Pivot
 *
 * Given a 0-indexed array nums and an integer pivot (guaranteed to be one of the values),
 * rearrange nums so that every element less than pivot comes first, then every element equal
 * to pivot, then every element greater than pivot. Within the "less than" group and within
 * the "greater than" group the original relative order must be preserved. Return the result.
 *
 * Input  : vector<int> nums, int pivot.
 * Output : vector<int> — the partitioned arrangement.
 *
 * Constraints: 1 <= n <= 1e5, -1e6 <= nums[i] <= 1e6, pivot occurs in nums.
 *
 * Approach: Three ordered groups built by two linear scans. First scan: append every value
 *   strictly less than pivot to the output in its original order, and count how many equal
 *   the pivot. Emit that many copies of pivot next. Second scan: append every value strictly
 *   greater than pivot, again in original order. Appending in traversal order makes both the
 *   "less" and "greater" runs stable automatically, and the pivot block sits between them.
 *
 * Complexity: O(n) time (two passes), O(n) space for the output.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> res;
        res.reserve(nums.size());

        int equalCount = 0;
        for (int v : nums) {
            if (v < pivot) res.push_back(v);   // "less" group, stable in traversal order
            else if (v == pivot) ++equalCount; // defer the pivot block to the middle
        }
        for (int i = 0; i < equalCount; ++i)
            res.push_back(pivot);              // all pivot copies between the two groups

        for (int v : nums)
            if (v > pivot) res.push_back(v);   // "greater" group, stable in traversal order

        return res;
    }
};
