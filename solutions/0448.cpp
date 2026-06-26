/*
 * LeetCode 448 - Find All Numbers Disappeared in an Array
 *
 * Given an array nums of n integers, every value in the range [1, n], return all
 * values in [1, n] that never appear in nums (duplicates in nums explain the gaps).
 *
 * Input  : vector<int>& nums (each entry in [1, n]). Output : vector<int> of the
 *          missing values, in ascending order.
 *
 * Constraints: 1 <= n <= 10^5; 1 <= nums[i] <= n. Values are exactly indexable into
 *   the array, which is what makes the in-place trick work.
 *
 * Approach: use the sign of each slot as a "seen" flag so no extra space is needed.
 *   Value v belongs at index v-1, so for each encountered value mark nums[|v|-1]
 *   negative. After one pass, an index still holding a positive value was never
 *   targeted, meaning i+1 is absent; collect those. Reading |v| ignores marks left
 *   by earlier steps, and since every value is in [1, n] the index is always valid.
 *
 * Complexity: O(n) time (two linear passes), O(1) extra space (the output list is
 *   not counted), matching the follow-up's requirements.
 */

#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = (int)nums.size();

        // Mark presence: flip the sign of the home slot for each value seen.
        for (int x : nums) {
            int idx = abs(x) - 1;                   // |x| undoes any earlier marking
            if (nums[idx] > 0)
                nums[idx] = -nums[idx];
        }

        // Any slot still positive was never marked, so its index+1 is missing.
        vector<int> missing;
        for (int i = 0; i < n; ++i)
            if (nums[i] > 0)
                missing.push_back(i + 1);

        return missing;
    }
};
