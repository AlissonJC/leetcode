/*
 * LeetCode 12 - Integer to Roman
 *
 * Convert an integer into its Roman numeral representation. Roman numerals use
 * seven base symbols (I=1, V=5, X=10, L=50, C=100, D=500, M=1000) and six
 * subtractive forms (IV=4, IX=9, XL=40, XC=90, CD=400, CM=900). The numeral is
 * built from the highest place value down to the lowest.
 *
 * Input  : int num. Output : string — the Roman numeral for num.
 *
 * Constraints: 1 <= num <= 3999.
 *
 * Approach: greedy with a fixed lookup table. List every token — the 7 base
 *   symbols together with the 6 subtractive forms — paired with its value and
 *   sorted in descending order of value. Scan the table once; for each token,
 *   append its symbol while the token's value still fits in what remains of num,
 *   subtracting as you go. Any valid Roman numeral is exactly this descending
 *   concatenation, so always consuming the largest fitting token is both correct
 *   and yields the canonical (shortest) form.
 *
 * Complexity: O(1) — the table is constant-size and num is bounded by 3999, so
 *   at most ~15 characters are produced.
 */

#include <string>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        // 13 tokens in descending value order: base symbols interleaved with the
        // subtractive forms so the greedy scan never needs special cases.
        static const int values[13] =
            {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        static const char* symbols[13] =
            {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string result;
        for (int i = 0; i < 13; ++i) {
            // Emit this token as many times as it divides into the remainder.
            while (num >= values[i]) {
                result += symbols[i];
                num -= values[i];
            }
        }
        return result;
    }
};
