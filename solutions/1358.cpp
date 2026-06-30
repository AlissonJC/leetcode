/*
 * LeetCode 1358 - Number of Substrings Containing All Three Characters
 *
 * Given a string s made up only of the characters 'a', 'b' and 'c', return the
 * number of substrings that contain at least one occurrence of all three.
 *
 * Input  : string s consisting solely of 'a', 'b', 'c'.
 * Output : count of substrings holding at least one 'a', one 'b' and one 'c'.
 * Constraints: 3 <= s.length <= 5e4.
 *
 * Approach: track the last index at which each of the three characters appeared.
 *   Fix the right endpoint i and let m = min(last['a'], last['b'], last['c']).
 *   Every left endpoint in [0, m] still leaves all three characters inside the
 *   window [left, i] (none of them was last seen after m), and no left > m can
 *   because the character last seen at m would drop out. So exactly m + 1
 *   substrings end at i. While some character has not appeared yet its last
 *   index is -1, making m = -1 and contributing 0 -- exactly right.
 *
 * Complexity: O(n) time (one pass), O(1) space (three counters).
 */

#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        int last[3] = {-1, -1, -1};            // last index of 'a', 'b', 'c'
        long long count = 0;                   // up to ~n*(n+1)/2 ~ 1.25e9; 64-bit is safe
        for (int i = 0; i < (int)s.size(); ++i) {
            last[s[i] - 'a'] = i;              // refresh the current character's position
            int m = min(last[0], min(last[1], last[2]));
            count += m + 1;                    // m == -1 (char still missing) adds nothing
        }
        return (int)count;
    }
};
