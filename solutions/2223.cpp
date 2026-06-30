/*
 * LeetCode 2223 - Sum of Scores of Built Strings
 *
 * A string s of length n is built one character at a time, each new character
 * PREPENDED to the front, so the string labeled s_i (length i) is the length-i
 * suffix of the final s. The score of s_i is the length of the longest common
 * prefix between s_i and the whole string s_n = s. Return the sum of the scores of
 * s_1, s_2, ..., s_n.
 *
 * Input  : string s. Output : long long — the summed scores.
 *
 * Constraints: 1 <= s.length <= 1e5; s is lowercase English letters. The sum can be
 *   as large as n*(n+1)/2 ~ 5e9 (e.g. s = "aaaa...a"), which overflows 32 bits, so the
 *   accumulator must be 64-bit.
 *
 * Approach: s_i is the suffix of s that begins at position p = n - i, so its score is
 *   the length of the longest common prefix of that suffix with s itself. That is
 *   exactly the Z-function: z[p] = LCP length of s and the suffix s[p..]. Hence the
 *   answer is the sum of all z[p], where z[0] is the whole string matching itself and
 *   therefore equals n. The Z-array is computed in linear time with the standard
 *   [l, r] window that reuses previously matched prefixes instead of rescanning.
 *
 * Complexity: O(n) time, O(n) space for the Z-array.
 */

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long sumScores(string s) {
        int n = (int)s.size();
        vector<int> z(n, 0);
        z[0] = n;                       // full string vs itself: prefix of length n

        // [l, r) is the rightmost prefix-match window discovered so far.
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            // Reuse the mirror value z[i-l] while it stays inside the known window.
            if (i < r) z[i] = min(r - i, z[i - l]);
            // Extend the match character by character beyond what was reused.
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            // Keep the window anchored at the farthest reach.
            if (i + z[i] > r) { l = i; r = i + z[i]; }
        }

        long long sum = 0;
        for (int i = 0; i < n; ++i) sum += z[i];   // z[i] is the score of suffix at i
        return sum;
    }
};
