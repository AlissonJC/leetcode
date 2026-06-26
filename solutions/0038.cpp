/*
 * LeetCode 38 - Count and Say
 *
 * The count-and-say sequence is defined recursively: countAndSay(1) = "1", and
 * countAndSay(n) is the run-length encoding of countAndSay(n-1). Run-length
 * encoding replaces each maximal block of equal consecutive characters by the
 * block's length followed by the character, e.g. "3322251" -> "23"+"32"+"15"+"11"
 * = "23321511". Return the n-th term as a string.
 *
 * Input  : int n. Output : string — the n-th count-and-say term.
 *
 * Constraints: 1 <= n <= 30. Terms grow but stay small (term 30 is a few thousand
 *   characters), so building each term from the previous one is cheap.
 *
 * Approach: iterative simulation (the asked-for iterative solution). Begin with
 *   "1" and apply run-length encoding n-1 times. Each pass walks the current
 *   string, and for every run of identical characters appends the run length
 *   (as decimal text, so runs of any size are handled) followed by the character.
 *   The n-th built string is the answer.
 *
 * Complexity: O(n * L) time where L is the length of the longest term reached
 *   (term length grows by a bounded factor each step); O(L) space for the strings.
 */

#include <string>
using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        string s = "1";                         // countAndSay(1)

        // Each iteration turns countAndSay(i) into countAndSay(i+1) via RLE.
        for (int i = 1; i < n; ++i) {
            string next;
            next.reserve(s.size() * 2);         // RLE rarely more than doubles length

            int j = 0, m = (int)s.size();
            while (j < m) {
                // Extend [j, k) over the maximal run of the same character.
                int k = j;
                while (k < m && s[k] == s[j])
                    ++k;

                // Emit "<run length><character>"; to_string covers runs > 9 safely.
                next += to_string(k - j);
                next += s[j];

                j = k;                          // jump past the run just encoded
            }

            s = move(next);
        }

        return s;
    }
};
