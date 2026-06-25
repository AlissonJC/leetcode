/*
 * LeetCode 7 - Reverse Integer
 *
 * Given a signed 32-bit integer x, return x with its decimal digits reversed.
 * If the reversed value would fall outside the signed 32-bit range
 * [-2^31, 2^31 - 1], return 0 instead. The environment is assumed NOT to allow
 * 64-bit integers, so overflow must be detected using 32-bit arithmetic alone.
 *
 * Input  : int x (function argument).
 * Output : int — the digit-reversed value, or 0 on overflow.
 *
 * Constraints: -2^31 <= x <= 2^31 - 1; no 64-bit (or wider) integer may be used.
 *
 * Approach: repeatedly pop the last digit of x with (x % 10) and drop it with
 *   (x /= 10), pushing it onto result via result = result * 10 + digit. Since a
 *   wider type is forbidden, check for overflow BEFORE performing that step:
 *   result * 10 + digit exceeds INT_MAX exactly when result > INT_MAX/10, or it
 *   equals INT_MAX/10 while digit is larger than the final allowed digit (7).
 *   The symmetric test against INT_MIN/10 (last digit -8) guards underflow.
 *   In C++ the % operator keeps the sign of the dividend and / truncates toward
 *   zero, so negative x flows through the same loop with negative digits — no
 *   separate sign handling is needed.
 *
 * Complexity: O(log10|x|) time (one iteration per digit); O(1) space.
 */

#include <climits>

class Solution {
public:
    int reverse(int x) {
        int result = 0;

        while (x != 0) {
            int digit = x % 10;   // for x < 0 this digit is negative (e.g. -123 % 10 == -3)
            x /= 10;              // truncates toward zero, so the loop terminates

            // Positive overflow: result*10 [+ digit] would pass INT_MAX (2147483647).
            // INT_MAX / 10 == 214748364 and its final digit is 7.
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7))
                return 0;
            // Negative overflow: result*10 [+ digit] would pass INT_MIN (-2147483648).
            // INT_MIN / 10 == -214748364 and its final digit is -8.
            if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8))
                return 0;

            result = result * 10 + digit;
        }

        return result;
    }
};
