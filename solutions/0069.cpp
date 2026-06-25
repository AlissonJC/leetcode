/*
 * LeetCode 69 - Sqrt(x)
 *
 * Given a non-negative integer x, return floor(sqrt(x)) -- the integer square
 * root -- without using any built-in exponent/sqrt function.
 *
 * Input  : int x.   Output: the largest integer k with k*k <= x.
 * Constraints: 0 <= x <= 2^31 - 1.
 *
 * Approach: binary-search the answer. floor(sqrt(x)) is the greatest k whose
 *   square does not exceed x, and "k*k <= x" is monotone in k, so binary search
 *   over [0, x] converges in O(log x). Use 64-bit for the candidate so mid*mid
 *   doesn't overflow -- near x = 2^31, the root ~46341 and 46341^2 already
 *   exceeds the 32-bit range.
 *
 * Complexity: O(log x) time, O(1) space.
 */

class Solution {
public:
    int mySqrt(int x) {
        long long lo = 0, hi = x, ans = 0;       // 64-bit to keep mid*mid safe
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (mid * mid <= x) {                // mid is feasible; try larger
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;                    // mid too big
            }
        }
        return (int)ans;
    }
};
