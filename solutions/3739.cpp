/*
 * LeetCode 3739 - Count Subarrays With Majority Element II
 *
 * Count the subarrays of nums in which `target` is the majority element -- i.e.
 * it appears strictly more than half the times of that subarray. This is the
 * hard version of 3737: the bound jumps to n <= 1e5, so the O(n^2) scan no
 * longer fits and the answer can reach ~5e9, hence the long long return type.
 *
 * Input  : vector<int> nums, int target.   Output: the number of such subarrays.
 * Constraints: 1 <= nums.length <= 1e5, 1 <= nums[i], target <= 1e9.
 *
 * Approach: reuse the same mapping as the easy version -- each element becomes
 *   +1 when it equals target and -1 otherwise. Build prefix sums P[0..n] with
 *   P[0] = 0. For the subarray nums[i..j-1] the mapped sum is P[j] - P[i], and
 *   target is its majority exactly when that sum is positive, i.e. P[i] < P[j]
 *   (a positive sum also forces count(target) >= 1, so target truly occurs).
 *   Every subarray maps to a unique prefix pair (i, j) with 0 <= i < j <= n, so
 *   the answer is the number of such pairs with P[i] < P[j]. Sweep j upward and,
 *   for each j, ask how many earlier P[i] are strictly smaller -- a classic
 *   "count smaller elements to the left" query answered with a Fenwick tree.
 *   Each P value lies in [-n, n], so shift by n into [1, 2n+1] and index the
 *   tree directly; no coordinate compression is needed.
 *
 * Complexity: O(n log n) time, O(n) space (the Fenwick tree over 2n+1 buckets).
 */

#include <vector>
using namespace std;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = (int)nums.size();

        // P[k] ranges over [-n, n]; shift each value by n and use 1-based Fenwick
        // indices, so a prefix sum P maps to tree position P + n + 1 in [1, 2n+1].
        int m = 2 * n + 1;                 // number of distinct shifted positions
        vector<int> bit(m + 1, 0);         // 1-indexed Fenwick tree of value counts

        // Register one occurrence of a shifted position.
        auto add = [&](int pos) {
            for (; pos <= m; pos += pos & (-pos)) ++bit[pos];
        };
        // Count how many registered values sit strictly below `pos`, i.e. how many
        // earlier prefix sums are strictly smaller than the current one.
        auto countLess = [&](int pos) {
            long long s = 0;
            for (int i = pos - 1; i > 0; i -= i & (-i)) s += bit[i];
            return s;
        };

        long long ans = 0;
        int prefix = 0;                    // P[0] = 0
        add(prefix + n + 1);               // make P[0] available as a left endpoint

        for (int k = 0; k < n; ++k) {
            prefix += (nums[k] == target) ? 1 : -1;   // prefix now equals P[k+1]
            int pos = prefix + n + 1;                 // shifted, 1-based position
            ans += countLess(pos);                    // earlier P[i] with P[i] < P[k+1]
            add(pos);                                 // expose P[k+1] to later j > k+1
        }
        return ans;
    }
};
