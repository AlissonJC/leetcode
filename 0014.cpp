/*
 * LeetCode 14 - Longest Common Prefix
 *
 * Find the longest string that is a prefix of every string in the array. If
 * there is no common prefix, return the empty string "".
 *
 * Input  : vector<string> strs.   Output: the longest common prefix.
 * Constraints: 1 <= strs.length <= 200, 0 <= strs[i].length <= 200,
 *              strs[i] is lowercase letters (when non-empty).
 *
 * Approach: vertical scanning. Walk the character positions of the first string;
 *   at position j every other string must have the same character at j (and be
 *   at least j+1 long). The first place this fails marks the end of the common
 *   prefix, so return strs[0][0..j). If no mismatch is ever found, the first
 *   string is itself the prefix. An empty string anywhere forces an empty result
 *   immediately at j = 0.
 *
 * Complexity: O(S) time where S is the total number of characters, O(1) space.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        for (int j = 0; j < (int)strs[0].size(); ++j) {
            char c = strs[0][j];                       // candidate prefix character
            for (int i = 1; i < (int)strs.size(); ++i)
                // mismatch, or this string ran out -> prefix ends here
                if (j >= (int)strs[i].size() || strs[i][j] != c)
                    return strs[0].substr(0, j);
        }
        return strs[0];                                // first string is fully a prefix
    }
};
