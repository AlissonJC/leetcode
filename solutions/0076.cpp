/*
 * LeetCode 76 - Minimum Window Substring
 *
 * Given strings s and t, return the SHORTEST substring of s that contains every
 * character of t including multiplicities (if t = "aab", the window must hold at
 * least two 'a' and one 'b'). Return "" when no such window exists. The answer is
 * guaranteed unique, so there is no tie to break.
 *
 * Input  : string s (length m), string t (length n).
 * Output : string — the minimum window substring, or "" if none.
 *
 * Constraints: 1 <= m, n <= 10^5; s and t are upper/lowercase English letters.
 *
 * Approach: an expand/contract sliding window. Count how many of each character
 *   t demands. `required` is the number of distinct characters that must be
 *   satisfied; `formed` is how many of those are currently met inside the window.
 *   Advance `right`, adding s[right] to the window; when a character's count
 *   reaches exactly what t needs, one more requirement is `formed`. While the
 *   window satisfies all requirements (formed == required) it is valid, so record
 *   it if it is the shortest so far and then shrink from the `left` to look for a
 *   tighter one, stopping as soon as some requirement drops below its quota. Each
 *   index is entered by `right` once and left by `left` once -> linear time, which
 *   meets the O(m + n) follow-up.
 *
 * Complexity: O(m + n) time (each pointer crosses s once, t scanned once to build
 *   the need table). O(1) space: fixed 128-slot arrays over the ASCII range.
 */

#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        // A window can never be shorter than t, so if s itself is shorter, give up.
        if (s.size() < t.size()) return "";

        // need[c] = how many times character c must appear in a valid window.
        // 128 slots cover all ASCII; the inputs are letters 'A'(65)..'z'(122).
        int need[128] = {0};
        for (char c : t) need[(int)c]++;

        // Number of DISTINCT characters whose quota must be met simultaneously.
        int required = 0;
        for (int c = 0; c < 128; ++c)
            if (need[c] > 0) ++required;

        int have[128] = {0};      // counts of each character inside the window
        int formed = 0;           // how many distinct quotas are currently met
        int bestLen = INT_MAX;    // length of the shortest valid window so far
        int bestStart = 0;        // start index of that shortest window
        int left = 0;             // left edge of the sliding window

        for (int right = 0; right < (int)s.size(); ++right) {
            int c = (int)s[right];
            have[c]++;
            // This character just reached its quota -> one more requirement met.
            if (need[c] > 0 && have[c] == need[c]) ++formed;

            // Window is valid: try to tighten it from the left as far as possible.
            while (formed == required) {
                int len = right - left + 1;
                if (len < bestLen) {        // strictly shorter -> new best window
                    bestLen = len;
                    bestStart = left;
                }
                // Remove the leftmost character and advance the left edge.
                int lc = (int)s[left];
                have[lc]--;
                // Dropping below quota breaks validity, ending the shrink phase.
                if (need[lc] > 0 && have[lc] < need[lc]) --formed;
                ++left;
            }
        }

        // No valid window was ever formed -> empty string per the problem.
        return bestLen == INT_MAX ? "" : s.substr(bestStart, bestLen);
    }
};
