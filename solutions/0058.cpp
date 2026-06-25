/*
 * LeetCode 58 - Length of Last Word
 *
 * Given a string s of words separated by spaces (possibly with trailing spaces),
 * return the length of the last word, where a word is a maximal run of
 * non-space characters.
 *
 * Input  : string s (English letters and spaces, at least one word).
 * Output : length of the final word.
 * Constraints: 1 <= s.length <= 1e4.
 *
 * Approach: scan from the end. First skip any trailing spaces to land on the
 *   last word's final character, then count characters while they are non-space.
 *   That count is the length of the last word.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int i = (int)s.size() - 1;
        while (i >= 0 && s[i] == ' ') --i;          // skip trailing spaces
        int len = 0;
        while (i >= 0 && s[i] != ' ') { --i; ++len; } // count the last word's chars
        return len;
    }
};
