/*
 * LeetCode 15 - 3Sum
 *
 * Given an integer array nums, return every unique triplet of values
 * [nums[i], nums[j], nums[k]] with distinct indices i, j, k whose sum is zero.
 * The returned set must not contain duplicate triplets (compared by value), and
 * the order of triplets and of elements within them does not matter.
 *
 * Input  : vector<int> nums. Output : all zero-sum triplets, deduplicated.
 *
 * Constraints: 3 <= n <= 3000; -1e5 <= nums[i] <= 1e5. A triplet sum has
 *   magnitude at most 3e5, so plain int never overflows.
 *
 * Approach: sort the array, then fix each element as the smallest member of the
 *   triplet and run a two-pointer scan over the suffix to its right, looking for
 *   a pair that sums to -nums[i]. Sorting buys two things: the pair search is
 *   O(n) per anchor (advance the left pointer when the sum is too small, the
 *   right pointer when it is too large), and equal values sit adjacent so they
 *   can be skipped at all three positions to avoid emitting duplicate triplets.
 *   Once the anchor value is positive the three sorted members can no longer sum
 *   to zero, so the outer loop stops early. O(n^2) is comfortable for n <= 3000,
 *   whereas the naive O(n^3) (~2.7e10) would be far too slow.
 *
 * Complexity: O(n^2) time (the sort is O(n log n), dominated by the nested
 *   two-pointer scan); O(1) extra space beyond the output.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = (int)nums.size();
        vector<vector<int>> result;

        for (int i = 0; i + 2 < n; ++i) {
            // Sorted ascending: if the smallest member is positive, no zero sum.
            if (nums[i] > 0) break;
            // Skip a repeated anchor so its triplets are not produced twice.
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int target = -nums[i];
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[l] + nums[r];
                if (sum == target) {
                    result.push_back({nums[i], nums[l], nums[r]});
                    // Move both pointers past their current values to skip
                    // duplicate pairs that would repeat this very triplet.
                    int lv = nums[l], rv = nums[r];
                    while (l < r && nums[l] == lv) ++l;
                    while (l < r && nums[r] == rv) --r;
                } else if (sum < target) {
                    ++l;                       // need a larger sum
                } else {
                    --r;                       // need a smaller sum
                }
            }
        }

        return result;
    }
};
