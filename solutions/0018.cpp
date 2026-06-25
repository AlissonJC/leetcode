/*
 * LeetCode 18 - 4Sum
 *
 * Given an integer array nums and an integer target, return every unique
 * quadruplet of values [nums[a], nums[b], nums[c], nums[d]] taken at four
 * distinct indices whose sum equals target. The returned set must not contain
 * duplicate quadruplets (compared by value); order does not matter.
 *
 * Input  : vector<int> nums, int target. Output : all summing quadruplets.
 *
 * Constraints: 1 <= n <= 200; -1e9 <= nums[i] <= 1e9; -1e9 <= target <= 1e9.
 *   Four values can sum to as much as +-4e9, and the intermediate quantity
 *   target - nums[i] - nums[j] reaches +-3e9 — both outside 32-bit range — so
 *   every running sum here must be held in a 64-bit integer.
 *
 * Approach: sort, then mirror the 3Sum structure one level deeper. Fix the first
 *   two members with nested loops i < j and reduce the rest to a 2Sum solved by a
 *   two-pointer sweep over the suffix to the right of j, searching for a pair that
 *   adds up to target - nums[i] - nums[j]. Sorting makes the inner pair search
 *   O(n) and places equal values adjacently, so duplicates are skipped at each of
 *   the four positions to avoid repeating a quadruplet. The required pair sum and
 *   the running pair sum are computed in long long to dodge 32-bit overflow.
 *   O(n^3) is comfortable for n up to 200.
 *
 * Complexity: O(n^3) time (the two-pointer inner loop nested in two outer loops);
 *   O(1) extra space beyond the output.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = (int)nums.size();
        vector<vector<int>> result;

        for (int i = 0; i + 3 < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;         // skip repeated first value
            for (int j = i + 1; j + 2 < n; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue; // skip repeated second value

                // 64-bit: target and two values can combine well beyond int range.
                long long need = (long long)target - nums[i] - nums[j];
                int l = j + 1, r = n - 1;
                while (l < r) {
                    long long sum = (long long)nums[l] + nums[r];
                    if (sum == need) {
                        result.push_back({nums[i], nums[j], nums[l], nums[r]});
                        int lv = nums[l], rv = nums[r];
                        while (l < r && nums[l] == lv) ++l;        // skip duplicate pairs
                        while (l < r && nums[r] == rv) --r;
                    } else if (sum < need) {
                        ++l;                                       // need a larger pair sum
                    } else {
                        --r;                                       // need a smaller pair sum
                    }
                }
            }
        }

        return result;
    }
};
