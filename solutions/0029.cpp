/*
 * LeetCode 29 - Divide Two Integers
 *
 * Return the quotient of dividend divided by divisor, truncated toward zero
 * (its fractional part dropped), computed WITHOUT the multiplication, division,
 * or modulo operators. The result must stay in the signed 32-bit range: a
 * quotient above 2^31 - 1 is clamped to 2^31 - 1 and one below -2^31 to -2^31.
 *
 * Input  : int dividend, int divisor (divisor != 0). Output : int — the clamped,
 *          truncated quotient.
 *
 * Constraints: -2^31 <= dividend, divisor <= 2^31 - 1; divisor != 0.
 *
 * Approach: binary long division using only shifts, additions, and subtractions.
 *   Convert both operands to non-negative magnitudes held in 64-bit integers —
 *   64-bit is required because |INT_MIN| = 2^31 does not fit in a 32-bit int.
 *   Then, from the highest shift down, subtract the largest shifted divisor
 *   (divisor << shift) that still fits in what remains of the dividend, adding the
 *   corresponding power of two (1 << shift) to the quotient; this reconstructs the
 *   quotient bit by bit. The sign is negative exactly when the two operands have
 *   different signs. The only quotient that overflows the 32-bit range is
 *   INT_MIN / -1 = 2^31, which is handled up front by returning INT_MAX.
 *
 * Complexity: O(log dividend) ~ 32 iterations; O(1) space.
 */

#include <climits>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        // The single overflowing quotient in 32-bit: clamp it to INT_MAX.
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;

        // 64-bit magnitudes: |INT_MIN| = 2^31 is not representable as a 32-bit int.
        long long a = llabs((long long)dividend);
        long long b = llabs((long long)divisor);
        bool negative = (dividend < 0) != (divisor < 0);   // sign of the result

        long long quotient = 0;
        // Subtract the largest shifted divisor that fits, high bit to low bit.
        for (int shift = 31; shift >= 0; --shift) {
            long long shifted = b << shift;
            if (shifted <= a) {
                a -= shifted;
                quotient += (1LL << shift);
            }
        }

        return negative ? (int)(-quotient) : (int)quotient;
    }
};
