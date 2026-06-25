/*
 * LeetCode 10 - Regular Expression Matching
 *
 * Given an input string s and a pattern p, decide whether p matches the ENTIRE
 * string s (not just a prefix). The pattern supports two special characters:
 *   '.'  matches any single character;
 *   '*'  matches zero or more copies of the element immediately before it.
 *
 * Input  : string s (lowercase letters), string p (lowercase letters, '.', '*').
 * Output : bool — true iff p matches all of s.
 *
 * Constraints: 1 <= s.length, p.length <= 20; every '*' is preceded by a valid
 *              character.
 *
 * Approach: dynamic programming over prefixes. Let dp[i][j] be true when the
 *   first i characters of s are matched by the first j characters of p. The
 *   pattern is consumed token by token, where a token is either a single
 *   character/'.' or a "x*" pair:
 *     - p[j-1] == '*': the token is p[j-2] followed by '*'. It can match zero
 *       copies (drop the token: dp[i][j-2]) or, if p[j-2] matches the current
 *       s[i-1], one more copy on top of an already-matched s[0..i-1] (dp[i-1][j]).
 *     - otherwise: a literal or '.', which must match s[i-1] and then reduce to
 *       dp[i-1][j-1].
 *   The empty pattern matches only the empty string, but an "x*" prefix can also
 *   match empty (zero copies), which seeds row 0. With lengths <= 20 the O(m*n)
 *   table is tiny.
 *
 * Complexity: O(m*n) time and O(m*n) space, m = s.length, n = p.length.
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

        // Row 0: empty s. Only "x*" groups can match it, by taking zero copies.
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*')
                dp[0][j] = dp[0][j - 2];       // j >= 2: every '*' has a preceding char
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    // Case A: the "x*" token matches zero copies — skip both chars.
                    dp[i][j] = dp[i][j - 2];
                    // Case B: x (== p[j-2]) matches s[i-1], so consume one more copy
                    // while the '*' token stays available for the rest of s.
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1])
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    // A single literal or '.' must consume exactly one char of s.
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }

        return dp[m][n];
    }
};
