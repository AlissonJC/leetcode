/*
 * LeetCode 44 - Wildcard Matching
 *
 * Given an input string s and a pattern p, decide whether p matches the ENTIRE
 * string s. The pattern supports two wildcards:
 *   '?'  matches any single character;
 *   '*'  matches any sequence of characters, including the empty sequence.
 *
 * Input  : string s (lowercase letters), string p (lowercase letters, '?', '*').
 * Output : bool — true iff p matches all of s.
 *
 * Constraints: 0 <= s.length, p.length <= 2000 (both may be empty).
 *
 * Approach: dynamic programming over prefixes. Let dp[i][j] be true when the
 *   first i characters of s are matched by the first j characters of p.
 *     - p[j-1] == '*': a star is free to match nothing (carry dp[i][j-1]) or to
 *       absorb one more character of s and stay open for the rest (dp[i-1][j]).
 *     - p[j-1] == '?' or it equals s[i-1]: consume exactly one character on each
 *       side, reducing to dp[i-1][j-1].
 *   Row 0 (empty s) is matchable only by a pattern that is all stars so far,
 *   hence dp[0][j] = dp[0][j-1] && p[j-1] == '*'.
 *   Contrast with problem 10: here '*' is a standalone "any run" wildcard, while
 *   in regex matching '*' modifies the single token immediately before it.
 *
 * Complexity: O(m*n) time and space (<= 2000*2000 = 4e6), m = s.length,
 *   n = p.length.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = (int)s.size(), n = (int)p.size();

        // dp[i][j] = does s[0..i) match p[0..j)
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;                       // empty pattern matches empty string

        // Row 0: empty s is matched by a leading run of '*' only.
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*')
                dp[0][j] = dp[0][j - 1];
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    // Match empty (skip the star) OR absorb s[i-1] and keep the star.
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    // '?' or an exact letter consumes one character on each side.
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }

        return dp[m][n];
    }
};
