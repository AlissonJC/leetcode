/*
 * LeetCode 65 - Valid Number
 *
 * Given a string s, decide whether it is a valid number. A valid number is an
 * integer or a decimal mantissa, optionally followed by an exponent:
 *   - integer  : [+-]? digits
 *   - decimal  : [+-]? ( digits '.' digits? | '.' digits )
 *   - exponent : [eE] [+-]? digits          (the part after e/E is a plain integer)
 * "digits" means one or more of 0-9. Examples that are valid: "2", "0089", "-0.1",
 * "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "53.5e93". Invalid: "abc", "1a",
 * "1e", "e3", "99e2.5", "--6", "-+3", ".", "e".
 *
 * Input  : string s. Output : bool — true iff s matches the grammar above.
 *
 * Constraints: 1 <= s.length <= 20; s contains only letters, digits, '+', '-', '.'.
 *   (No spaces in this version of the problem, so no trimming is required.)
 *
 * Approach: One left-to-right pass, treating the string as a tiny finite-state
 *   machine summarized by three flags — whether a digit, a dot, and an exponent
 *   have appeared so far. Each character type is legal only in specific contexts:
 *     digit : always fine; marks that the current run has a digit.
 *     '+'/'-' : only at index 0 or immediately after 'e'/'E' (a sign starts the
 *               mantissa or the exponent, nowhere else).
 *     '.'   : only if no dot and no exponent seen yet (an exponent's argument is a
 *               plain integer, so it cannot contain a dot; and only one dot total).
 *     'e'/'E' : only if not seen before AND at least one digit precedes it. After it
 *               we reset the digit flag, which forces at least one digit to follow.
 *     anything else : invalid.
 *   The string is valid exactly when the scan finishes with the digit flag set,
 *   which simultaneously guarantees the mantissa had a digit and, if an exponent
 *   was present, that the exponent had a digit too.
 *
 * Complexity: O(n) time, O(1) space, where n = s.length() <= 20.
 */

#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        bool seenDigit = false;   // a digit appeared in the current mantissa/exponent run
        bool seenDot   = false;   // a '.' has appeared (only allowed in the mantissa)
        bool seenExp   = false;   // an 'e'/'E' has appeared

        int n = (int)s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isdigit((unsigned char)c)) {
                seenDigit = true;
            } else if (c == '+' || c == '-') {
                // A sign is valid only leading the whole string or right after e/E.
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') return false;
            } else if (c == '.') {
                // Second dot, or a dot inside the exponent, is illegal.
                if (seenDot || seenExp) return false;
                seenDot = true;
            } else if (c == 'e' || c == 'E') {
                // Need exactly one exponent, and a digit must precede it.
                if (seenExp || !seenDigit) return false;
                seenExp = true;
                seenDigit = false;    // require at least one digit after the exponent
            } else {
                return false;         // any other character (letters, etc.) is invalid
            }
        }
        // Valid iff a digit closes the string: covers "no digits at all" and a
        // dangling exponent like "1e" (seenDigit was reset and never set again).
        return seenDigit;
    }
};
