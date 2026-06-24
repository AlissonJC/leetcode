/*
 * LeetCode 13 - Roman to Integer
 *
 * Convert a valid Roman numeral string to its integer value. Symbols and values:
 * I=1, V=5, X=10, L=50, C=100, D=500, M=1000. Numerals run largest-to-smallest,
 * except for six subtractive pairs (IV, IX, XL, XC, CD, CM).
 *
 * Input  : string s (a valid Roman numeral, value in [1, 3999]).
 * Output : the integer it represents.
 * Constraints: 1 <= s.length <= 15; s uses only the seven Roman symbols.
 *
 * Approach: give each symbol its value and scan left to right. A symbol that is
 *   smaller than the symbol immediately after it forms a subtractive pair, so
 *   subtract it; otherwise add it. One pass handles both the additive and the
 *   subtractive cases without special-casing the six pairs explicitly.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> val = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };
        int total = 0, n = (int)s.size();
        for (int i = 0; i < n; ++i) {
            // Subtractive pair: a smaller symbol just before a larger one.
            if (i + 1 < n && val[s[i]] < val[s[i + 1]]) total -= val[s[i]];
            else total += val[s[i]];
        }
        return total;
    }
};
