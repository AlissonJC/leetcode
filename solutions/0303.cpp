/*
 * LeetCode 303 - Range Sum Query - Immutable
 *
 * Design a class over a fixed (immutable) integer array that answers many range-sum
 * queries. sumRange(left, right) must return nums[left] + ... + nums[right].
 *
 *   NumArray(vector<int> nums) : store the array / precompute helpers.
 *   int sumRange(int left, int right) : sum of the inclusive range [left, right].
 *
 * Input/Output: method calls (no stdin/stdout); sumRange returns an int.
 *
 * Constraints: 1 <= n <= 1e4, -1e5 <= nums[i] <= 1e5, 0 <= left <= right < n,
 *   up to 1e4 calls to sumRange.
 *
 * Approach: Prefix sums. Precompute pre[i] = nums[0] + ... + nums[i-1] with pre[0] = 0, so
 *   any inclusive range sum is a single subtraction: sumRange(l, r) = pre[r+1] - pre[l].
 *   Building pre is one linear pass; every query is then O(1). The extra +1 slot lets l = 0
 *   be handled without a special case.
 *
 * Overflow: a prefix value can reach n * max|nums| = 1e4 * 1e5 = 1e9; the difference is a
 *   genuine subarray sum, also within +/-1e9 (< int max), but pre is kept in 64-bit so the
 *   subtraction never even flirts with overflow.
 *
 * Complexity: O(n) construction, O(1) per query; O(n) space.
 */

#include <vector>
using namespace std;

class NumArray {
    vector<long long> pre;                 // pre[i] = sum of nums[0..i-1]

public:
    NumArray(vector<int>& nums) {
        int n = (int)nums.size();
        pre.assign(n + 1, 0);              // pre[0] = 0 sentinel simplifies left == 0
        for (int i = 0; i < n; ++i)
            pre[i + 1] = pre[i] + nums[i]; // running total up to and including index i
    }

    int sumRange(int left, int right) {
        // Range [left, right] = (prefix through right) minus (prefix before left).
        return (int)(pre[right + 1] - pre[left]);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
