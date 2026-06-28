/*
 * LeetCode 224 - Basic Calculator
 *
 * Evaluate a string expression and return its integer value, without using any
 * built-in expression evaluator. The expression contains only non-negative
 * integers, '+', '-', '(', ')' and spaces. '+' is always binary, but '-' may be
 * unary (e.g. "-1" or "-(2 + 3)"); there are never two consecutive operators and
 * the expression is guaranteed valid. There is no multiplication or division, so
 * operator precedence is flat — only the parentheses introduce nesting.
 *
 * Input  : string s. Output : int — the evaluated result.
 *
 * Constraints: 1 <= s.length <= 3e5; characters are digits, '+', '-', '(', ')',
 *   ' '. Every number and every running calculation fits in a signed 32-bit
 *   integer, so the arithmetic cannot overflow (a wider accumulator is used
 *   anyway, purely defensively).
 *
 * Approach: a single left-to-right scan with a running total, a current sign,
 *   and a stack. Because there is no precedence beyond parentheses, each number
 *   can be folded into the result the moment the next operator (or end of a
 *   parenthesised group) is reached, multiplied by the sign that preceded it.
 *   A '(' starts a fresh sub-expression: push the result accumulated so far and
 *   the sign that applies to the whole group, then reset. A ')' closes the group
 *   by folding in the last pending number, popping that saved sign and outer
 *   result, and combining them (outer + savedSign * inner). This treats a unary
 *   minus uniformly, since the sign simply starts as -1 for that term.
 *
 * Complexity: O(n) time — one pass over the string; O(n) space in the worst case
 *   for the parenthesis stack (deeply nested input).
 */

#include <string>
#include <stack>
#include <cctype>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        long long result = 0;   // running total of the current parenthesis level
        long long number = 0;   // integer currently being parsed
        int sign = 1;           // sign applied to `number` when it is folded in
        stack<long long> st;    // saves, per '(', the outer result then its sign

        for (char c : s) {
            if (isdigit(static_cast<unsigned char>(c))) {
                // Build the multi-digit number one character at a time.
                number = number * 10 + (c - '0');
            } else if (c == '+') {
                result += sign * number;   // commit the pending term...
                number = 0;
                sign = 1;                  // ...next term is added
            } else if (c == '-') {
                result += sign * number;
                number = 0;
                sign = -1;                 // next term is subtracted (also covers unary '-')
            } else if (c == '(') {
                // Begin a nested expression: remember where we were and the sign
                // that the whole group will be multiplied by, then start clean.
                st.push(result);
                st.push(sign);
                result = 0;
                sign = 1;
            } else if (c == ')') {
                result += sign * number;   // fold the last number inside the group
                number = 0;
                long long savedSign = st.top(); st.pop();
                long long outer     = st.top(); st.pop();
                // Combine the group's value with the result outside the '('.
                result = outer + savedSign * result;
            }
            // Spaces and any other separator are simply skipped.
        }

        // Commit the final pending term (no trailing operator triggers it).
        result += sign * number;
        return static_cast<int>(result);
    }
};
