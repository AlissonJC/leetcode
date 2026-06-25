/*
 * LeetCode 5 - Longest Palindromic Substring
 *
 * Given a string s, return the longest contiguous substring of s that reads the
 * same forwards and backwards. If several substrings share the maximum length,
 * any one of them is accepted.
 *
 * Input  : string s (function argument, no stdin/stdout).
 * Output : the longest palindromic substring of s.
 *
 * Constraints: 1 <= s.length <= 1000; s consists of digits and English letters.
 *
 * Approach: expand around center. Every palindrome has a center — either a
 *   single character (for odd lengths) or the gap between two characters (for
 *   even lengths), which gives 2n-1 possible centers. For each center, push two
 *   pointers outward as long as the mirrored characters match; the widest span
 *   found over all centers is the answer. With n <= 1000 the quadratic work is
 *   about 10^6 operations, well within the time limit, so the simpler O(1)-space
 *   center expansion is preferred over Manacher's O(n).
 *
 * Complexity: O(n^2) time — 2n-1 centers, each expanding up to O(n); O(1) extra
 *   space (only indices are tracked, the result is sliced from s at the end).
 */

#include <string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";          // guard; constraints say n >= 1 anyway

        int bestStart = 0, bestLen = 1;    // a single character is always a palindrome

        // Grow a palindrome outward from the center (left, right) and, if it
        // beats the current best, record its start index and length. After the
        // loop the matched palindrome occupies the interval [left+1, right-1].
        auto expand = [&](int left, int right) {
            while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
                --left;
                ++right;
            }
            int len = right - left - 1;
            if (len > bestLen) {
                bestLen = len;
                bestStart = left + 1;
            }
        };

        for (int i = 0; i < (int)s.size(); ++i) {
            expand(i, i);          // odd-length palindrome centered on s[i]
            expand(i, i + 1);      // even-length palindrome centered between s[i] and s[i+1]
        }

        return s.substr(bestStart, bestLen);
    }
};
