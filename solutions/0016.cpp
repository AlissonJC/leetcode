/*
 * LeetCode 16 - 3Sum Closest
 *
 * Given an integer array nums and an integer target, choose three elements at
 * distinct indices whose sum is as close as possible to target, and return that
 * sum. Each input is guaranteed to have exactly one closest sum.
 *
 * Input  : vector<int> nums, int target. Output : int — the closest achievable
 *          three-element sum.
 *
 * Constraints: 3 <= n <= 500; -1000 <= nums[i] <= 1000; -1e4 <= target <= 1e4.
 *   A triple sum lies in [-3000, 3000], so plain int never overflows.
 *
 * Approach: the same sort-then-two-pointer skeleton as 3Sum, but instead of
 *   hunting for an exact sum we keep the triple whose sum is nearest target.
 *   After sorting, fix each element as the smallest of the triple and sweep the
 *   remaining suffix with two pointers: if the current sum is below target move
 *   the left pointer right to raise it, if above move the right pointer left to
 *   lower it, and whenever the sum is closer than the best so far record it. A
 *   sum exactly equal to target is optimal and returns immediately. O(n^2) is
 *   comfortable for n up to 500.
 *
 * Complexity: O(n^2) time (sort is O(n log n), dominated by the nested
 *   two-pointer sweep); O(1) extra space.
 */

#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = (int)nums.size();
        int best = nums[0] + nums[1] + nums[2];   // seed with any valid triple

        for (int i = 0; i + 2 < n; ++i) {
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (abs(sum - target) < abs(best - target))
                    best = sum;                    // strictly closer to target
                if (sum == target)
                    return target;                 // exact hit: cannot do better
                if (sum < target) ++l;             // too small -> need a larger sum
                else              --r;             // too large -> need a smaller sum
            }
        }
        return best;
    }
};
