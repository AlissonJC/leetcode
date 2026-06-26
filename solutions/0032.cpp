/*
 * LeetCode 32 - Longest Valid Parentheses
 *
 * Given a string s made only of '(' and ')', return the length of the longest
 * contiguous substring that is well-formed (every '(' has a matching ')' and the
 * matches nest properly).
 *
 * Input  : string s. Output : int — length of the longest valid substring.
 *
 * Constraints: 0 <= s.length <= 3*10^4; each s[i] is '(' or ')'. Lengths fit in a
 *   32-bit int, and the linear scan below is far inside any limit.
 *
 * Approach: scan once with a stack of INDICES. The invariant is that the value on
 *   top of the stack is always the index of the last position that a valid run
 *   cannot extend past — either an unmatched ')' or a sentinel sitting just before
 *   the string. Seed the stack with -1 so the first valid run is measured from
 *   "position before index 0". For '(' push its index. For ')' pop one entry: if
 *   the stack becomes empty this ')' is unmatched, so push its own index as the
 *   new boundary; otherwise the closer matched something, and the current valid
 *   length is i - stack.top() (distance back to the last boundary). Track the max.
 *
 * Complexity: O(n) time (each index is pushed and popped at most once); O(n) space
 *   for the stack.
 */

#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int best = 0;

        // Stack holds indices of boundaries. The -1 sentinel represents the
        // position just before the string, so a valid run that starts at index 0
        // is measured correctly as i - (-1).
        stack<int> st;
        st.push(-1);

        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == '(') {
                // Opening bracket: its index becomes a potential match target.
                st.push(i);
            } else {
                // Closing bracket: consume the most recent boundary/opener.
                st.pop();
                if (st.empty()) {
                    // No opener to match this ')'. It is itself unmatched, so it
                    // becomes the new left boundary for any future valid run.
                    st.push(i);
                } else {
                    // Matched: everything from just after st.top() up to i is valid.
                    best = max(best, i - st.top());
                }
            }
        }

        return best;
    }
};
