/*
 * LeetCode 72 - Edit Distance
 *
 * Given two strings word1 and word2, return the minimum number of single-character
 * operations needed to turn word1 into word2, where an operation is inserting a
 * character, deleting a character, or replacing a character. This value is the
 * classic Levenshtein edit distance.
 *
 * Input  : string word1, string word2. Output : int — the minimum number of edits.
 *
 * Constraints: 0 <= word1.length, word2.length <= 500; both are lowercase letters.
 *
 * Approach: Dynamic programming over prefixes. Let dp[i][j] be the edit distance
 *   between the first i characters of word1 and the first j characters of word2.
 *   Turning a prefix into the empty string costs one delete per character, and
 *   building a prefix from empty costs one insert per character, giving the base
 *   cases dp[i][0] = i and dp[0][j] = j. For the general cell, if the two current
 *   characters match, no edit is needed and dp[i][j] = dp[i-1][j-1]; otherwise take
 *   one edit plus the cheapest of the three moves — replace (dp[i-1][j-1]), delete
 *   from word1 (dp[i-1][j]), or insert into word1 (dp[i][j-1]). The answer is dp[m][n].
 *   A full (m+1) x (n+1) table is used for clarity; with m, n <= 500 it is tiny.
 *
 * Complexity: O(m * n) time and O(m * n) space, m = word1.length, n = word2.length.
 */

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = (int)word1.size(), n = (int)word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Base cases: converting a prefix to/from the empty string.
        for (int i = 0; i <= m; ++i) dp[i][0] = i;   // delete i characters
        for (int j = 0; j <= n; ++j) dp[0][j] = j;   // insert j characters

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    // Characters align — carry the diagonal cost, no edit here.
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // One edit plus the best of replace / delete / insert.
                    dp[i][j] = 1 + min({ dp[i - 1][j - 1],   // replace word1[i-1]
                                         dp[i - 1][j],        // delete word1[i-1]
                                         dp[i][j - 1] });     // insert word2[j-1]
                }
            }
        }
        return dp[m][n];
    }
};
