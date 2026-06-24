/*
 * LeetCode 3838 - Weighted Word Mapping
 *
 * Each lowercase letter i has weight weights[i]. A word's weight is the sum of
 * its letters' weights. For each word, take that weight modulo 26 and map the
 * result to a letter in reverse alphabetical order (0 -> 'z', 1 -> 'y', ...,
 * 25 -> 'a'). Return the concatenation of the mapped letters, in word order.
 *
 * Input  : vector<string> words, vector<int> weights (length 26).
 * Output : a string, one mapped character per word.
 * Constraints: 1 <= words.length <= 100, 1 <= words[i].length <= 10,
 *              weights.length == 26, 1 <= weights[i] <= 100.
 *
 * Approach: directly sum the per-letter weights of each word (at most 10*100 =
 *   1000, far inside int range), reduce modulo 26, and convert index k to the
 *   reverse-order letter 'z' - k. Append one character per word.
 *
 * Complexity: O(total length of all words) time, O(1) extra space.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;
        result.reserve(words.size());                 // exactly one char per word
        for (const string& w : words) {
            int sum = 0;
            for (char c : w) sum += weights[c - 'a'];  // weight of the word
            // Reverse alphabetical map: index 0 -> 'z', ..., 25 -> 'a'.
            result += char('z' - sum % 26);
        }
        return result;
    }
};
