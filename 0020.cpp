/*
 * LeetCode 20 - Valid Parentheses
 *
 * Given a string of brackets '()[]{}', decide whether it is valid: every opening
 * bracket is closed by the same type, in the correct order, and every closing
 * bracket has a matching opening one.
 *
 * Input  : string s (brackets only).   Output: bool.
 * Constraints: 1 <= s.length <= 1e4.
 *
 * Approach: scan left to right with a stack of unmatched opening brackets. Push
 *   each opener; on a closer, the most recent unmatched opener (the stack top)
 *   must be its partner -- otherwise the string is invalid. A closer with an
 *   empty stack has no partner, and any openers left over at the end are
 *   unmatched, so the string is valid exactly when the stack ends empty.
 *
 * Complexity: O(n) time, O(n) space (the stack).
 */

#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> open;                          // unmatched opening brackets
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                open.push(c);
            } else {
                if (open.empty()) return false;     // closer with nothing to match
                char t = open.top();
                if ((c == ')' && t != '(') ||
                    (c == ']' && t != '[') ||
                    (c == '}' && t != '{')) return false;  // type mismatch
                open.pop();
            }
        }
        return open.empty();                        // leftover openers => invalid
    }
};
