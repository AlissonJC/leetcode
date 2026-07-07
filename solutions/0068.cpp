/*
 * LeetCode 68 - Text Justification
 *
 * Given an array of words and a line width maxWidth, format the words into fully
 * justified lines of exactly maxWidth characters. Pack words greedily (as many per
 * line as fit). On a fully justified line the gaps between words share the leftover
 * spaces as evenly as possible, with the leftmost gaps taking the extra when it does
 * not divide evenly. The last line, and any line holding a single word, is instead
 * left-justified: single spaces between words and the remaining width padded on the
 * right.
 *
 * Input  : vector<string> words, int maxWidth.
 * Output : vector<string> — each string is exactly maxWidth characters.
 *
 * Constraints: 1 <= words.length <= 300; 1 <= words[i].length <= maxWidth <= 100.
 *   Every word fits on a line by itself, so greedy packing never stalls.
 *
 * Approach: Sweep the words once. For the current line, extend the window [i, j)
 *   while the words plus one mandatory space per existing gap still fit:
 *   sumWordLen + words[j] + (gapsSoFar) <= maxWidth. Once the window is fixed, render:
 *     - If this is the last window (j == n) or it holds one word (gaps == 0), left-
 *       justify: join with single spaces and pad the right up to maxWidth.
 *     - Otherwise distribute totalSpaces = maxWidth - sumWordLen across gaps = count-1
 *       slots: every gap gets base = totalSpaces / gaps, and the first
 *       extra = totalSpaces % gaps gaps get one more, so wider gaps sit on the left.
 *   Move i to j and repeat.
 *
 * Complexity: O(total characters of output) time — each character is written once;
 *   O(1) extra space beyond the output.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = (int)words.size();
        int i = 0;

        while (i < n) {
            // Grow the line window [i, j). `lineLen` is the sum of raw word lengths;
            // (j - i) counts the words already chosen, i.e. the minimum spaces needed
            // if we add one more word (one space per existing gap).
            int j = i, lineLen = 0;
            while (j < n && lineLen + (int)words[j].size() + (j - i) <= maxWidth) {
                lineLen += (int)words[j].size();
                ++j;
            }

            int count = j - i;          // words on this line
            int gaps  = count - 1;      // gaps between them
            string line;

            if (j == n || gaps == 0) {
                // Last line, or a single-word line: left-justify with single spaces...
                for (int k = i; k < j; ++k) {
                    line += words[k];
                    if (k < j - 1) line += ' ';
                }
                // ...then pad the remaining width on the right.
                line += string(maxWidth - (int)line.size(), ' ');
            } else {
                // Fully justify: spread the leftover width across the gaps.
                int totalSpaces = maxWidth - lineLen;
                int base  = totalSpaces / gaps;   // every gap gets at least this many
                int extra = totalSpaces % gaps;   // leftmost `extra` gaps get one more
                for (int k = i; k < j; ++k) {
                    line += words[k];
                    if (k < j - 1) {
                        int sp = base + ((k - i) < extra ? 1 : 0);
                        line += string(sp, ' ');
                    }
                }
            }

            result.push_back(line);
            i = j;                       // next line starts at the first unplaced word
        }
        return result;
    }
};
