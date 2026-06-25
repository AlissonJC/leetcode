/*
 * LeetCode 8 - String to Integer (atoi)
 *
 * Implement myAtoi: convert the leading numeric portion of a string into a
 * 32-bit signed integer following four steps:
 *   1. skip any leading space (' ') characters;
 *   2. read an optional single sign, '+' or '-' (default positive);
 *   3. read consecutive decimal digits, stopping at the first non-digit or the
 *      end of the string (leading zeros are absorbed naturally);
 *   4. clamp the result into [-2^31, 2^31 - 1]; values below the range become
 *      -2^31 and values above it become 2^31 - 1.
 *  If no digits are read at all, the result is 0.
 *
 * Input  : string s. Output : the parsed, clamped 32-bit integer.
 *
 * Constraints: 0 <= s.length <= 200; s holds English letters, digits, ' ',
 *              '+', '-' and '.'.
 *
 * Approach: a single left-to-right scan with an index cursor moving through the
 *   four phases. Because the string may contain up to 200 digits, the true value
 *   can dwarf even a 64-bit type, so the magnitude is accumulated in a long long
 *   and clamped the moment it would cross the signed-32-bit bound. Early clamping
 *   keeps the accumulator from ever exceeding ~2.1e10, which is safely inside
 *   long long. The negative bound uses magnitude 2147483648 so that the exact
 *   value INT_MIN is representable rather than wrongly clamped.
 *
 * Complexity: O(n) time over the string; O(1) extra space.
 */

#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int n = (int)s.size();

        // Phase 1: skip leading spaces (only ' ' per the statement).
        while (i < n && s[i] == ' ')
            ++i;

        // Phase 2: optional single sign character.
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-')
                sign = -1;
            ++i;
        }

        // Phase 3: accumulate digit magnitude, clamping as soon as it overflows.
        long long magnitude = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            magnitude = magnitude * 10 + (s[i] - '0');

            // Clamp immediately so the accumulator can never run away over 200
            // digits. Positive bound is INT_MAX; negative bound is |INT_MIN|.
            if (sign == 1 && magnitude > INT_MAX)
                return INT_MAX;
            if (sign == -1 && -magnitude < INT_MIN)   // -magnitude < -2147483648
                return INT_MIN;

            ++i;
        }

        // In range: sign * magnitude fits exactly in int (INT_MIN included).
        return (int)(sign * magnitude);
    }
};
