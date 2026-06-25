/*
 * LeetCode 3 - Longest Substring Without Repeating Characters
 *
 * Given a string s, return the length of the longest substring that contains no
 * repeated character.
 *
 * Input  : string s (English letters, digits, symbols, spaces -- ASCII).
 * Output : length of the longest duplicate-free substring.
 * Constraints: 0 <= s.length <= 5e4.
 *
 * Approach: sliding window. Keep a window [left, right] with all-distinct
 *   characters and, for each character, its most recent index. When s[right] was
 *   last seen at an index inside the current window (>= left), jump left to one
 *   past that occurrence so the window stays duplicate-free. Record the window
 *   width right - left + 1 at every step; the maximum is the answer.
 *
 * Complexity: O(n) time, O(1) space (fixed 256-entry last-seen table).
 */

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(256, -1);                 // last index each ASCII char appeared
        int best = 0, left = 0;
        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char c = (unsigned char)s[right];
            if (last[c] >= left) left = last[c] + 1; // shrink past the previous duplicate
            last[c] = right;
            best = max(best, right - left + 1);
        }
        return best;
    }
};
