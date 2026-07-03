/*
 * LeetCode 50 - Pow(x, n)
 *
 * Implement pow(x, n), which raises the real number x to the integer power n.
 * n is a signed 32-bit integer and may be negative, zero, or positive.
 *
 * Input  : double x, int n.
 * Output : double - the value of x raised to the power n.
 *
 * Constraints: -100.0 < x < 100.0; -2^31 <= n <= 2^31 - 1; n is an integer;
 *   either x is not zero or n > 0; -10^4 <= x^n <= 10^4.
 *
 * Approach: exponentiation by squaring. Rather than multiply x by itself n
 *   times (O(n)), walk the binary representation of the exponent: repeatedly
 *   square the base, and whenever the current low bit of the exponent is 1,
 *   fold the current base into the running result. This computes x^n in
 *   O(log|n|) multiplications, since x^n = product of x^(2^k) over the set bits
 *   k of n. A negative exponent is handled by x^n = (1/x)^(-n).
 *
 *   Critical detail: the exponent is widened to a 64-bit long long BEFORE it is
 *   negated. n can be INT_MIN = -2^31, and -INT_MIN = 2^31 does not fit in a
 *   32-bit int (it overflows to itself, a silent bug). Promoting to long long
 *   first makes the negation safe.
 *
 * Complexity: O(log|n|) time - one iteration per bit of the exponent; O(1)
 *   extra space.
 */

#include <cmath>  // (only for the header's sake; not used in the logic)
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        // Widen to 64-bit FIRST so that negating INT_MIN cannot overflow.
        long long exp = n;

        // Negative power: x^n == (1/x)^(-n). Now -exp is safe in long long.
        if (exp < 0) {
            x = 1.0 / x;
            exp = -exp;
        }

        // Binary exponentiation: accumulate x^(2^k) for each set bit k of exp.
        double result = 1.0;
        while (exp > 0) {
            if (exp & 1LL) result *= x;  // current bit set -> include this power of x
            x *= x;                      // advance base to the next squared power
            exp >>= 1;                   // consume the processed bit
        }
        return result;
    }
};
