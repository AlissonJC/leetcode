/*
 * LeetCode 30 - Substring with Concatenation of All Words
 *
 * Given a string s and an array words whose strings ALL share the same length,
 * a "concatenated substring" is any window of s equal to some permutation of
 * words glued together (each word used exactly as many times as it appears in
 * words). Return the start indices of every such window. Order does not matter.
 *
 * Input  : string s, vector<string>& words (all words same length).
 * Output : vector<int> — every starting index of a concatenated substring.
 *
 * Constraints: 1 <= s.length <= 10^4; 1 <= words.length <= 5000;
 *              1 <= words[i].length <= 30; s and words[i] are lowercase letters.
 *
 * Approach: sliding window advancing one whole word at a time. Every valid
 *   window has length numWords * wordLen and starts at an index whose remainder
 *   modulo wordLen is fixed, so running wordLen independent windows (offsets
 *   0..wordLen-1) covers all candidates. Within an offset, read s word by word:
 *   keep a frequency map of the words currently in the window. If an incoming
 *   word is not in the target multiset, the window cannot extend past it, so
 *   drop everything and restart after it. If it is a target word but now exceeds
 *   its needed count, shrink from the left (one word at a time) until the excess
 *   is gone. Whenever the window holds exactly numWords target words it is a
 *   full match: record its left index, then slide one word forward to keep
 *   searching for overlapping matches.
 *
 * Complexity: each word position is added to and removed from the window at most
 *   once per offset, and there are n/wordLen positions across all offsets, each
 *   costing O(wordLen) to extract/hash -> O(n * wordLen) time. Space O(numWords *
 *   wordLen) for the frequency maps. With n <= 10^4 this is far within limits.
 */

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        int n = (int)s.size();
        int numWords = (int)words.size();
        int wordLen = (int)words[0].size();          // all words share this length
        int windowLen = numWords * wordLen;           // length of a full match
        if (n < windowLen) return result;             // s too short to fit one

        // Target multiset: how many times each word must appear in a window.
        unordered_map<string, int> need;
        for (const string& w : words) need[w]++;

        // Each valid start index has a fixed remainder modulo wordLen, so trying
        // every offset in [0, wordLen) examines every possible alignment exactly.
        for (int offset = 0; offset < wordLen; ++offset) {
            unordered_map<string, int> window;        // words currently in window
            int count = 0;                            // how many words in window
            int left = offset;                        // window's left boundary

            // Walk forward one word at a time from this offset to the end.
            for (int right = offset; right + wordLen <= n; right += wordLen) {
                string word = s.substr(right, wordLen);

                if (need.find(word) == need.end()) {
                    // A word outside the target set breaks any window crossing it,
                    // so discard the current window and restart just past it.
                    window.clear();
                    count = 0;
                    left = right + wordLen;
                    continue;
                }

                // Admit the target word into the window.
                window[word]++;
                count++;

                // If this word now appears more often than needed, slide the left
                // edge forward, dropping words, until the surplus is removed.
                while (window[word] > need[word]) {
                    string leftWord = s.substr(left, wordLen);
                    window[leftWord]--;
                    left += wordLen;
                    count--;
                }

                // Exactly numWords target words with correct multiplicities: match.
                if (count == numWords) {
                    result.push_back(left);
                    // Slide one word forward so overlapping matches are still found.
                    string leftWord = s.substr(left, wordLen);
                    window[leftWord]--;
                    left += wordLen;
                    count--;
                }
            }
        }

        return result;
    }
};
