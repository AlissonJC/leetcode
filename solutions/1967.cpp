/*
 * LeetCode 1967 - Number of Strings That Appear as Substrings in Word
 *
 * Given an array of strings patterns and a string word, return how many of the
 * patterns occur as a (contiguous) substring of word.
 *
 * Input  : vector<string> patterns, string word (all lowercase English letters).
 * Output : count of patterns[i] that appear inside word.
 * Constraints: 1 <= patterns.length, patterns[i].length, word.length <= 100.
 *
 * Approach: the bounds are tiny, so test each pattern directly with the standard
 *   library substring search -- string::find returns string::npos when the
 *   pattern is absent. Count every pattern that is found. No fancier algorithm
 *   (KMP, suffix automaton) is needed at these sizes.
 *
 * Complexity: O(P * |word| * |pattern|) worst case (<= ~1e6 char comparisons),
 *   O(1) extra space.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;
        for (const string& p : patterns)
            if (word.find(p) != string::npos)   // npos => p is not a substring of word
                ++count;
        return count;
    }
};
