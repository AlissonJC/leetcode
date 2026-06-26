/*
 * LeetCode 22 - Generate Parentheses
 *
 * Given n pairs of parentheses, generate every combination of well-formed
 * (balanced) parentheses that can be built from them. The results may be returned
 * in any order.
 *
 * Input  : int n. Output : vector<string> of all valid sequences (length 2n each).
 *
 * Constraints: 1 <= n <= 8. The count of valid sequences is the nth Catalan
 *   number, so the output stays small (C(8) = 1430).
 *
 * Approach: backtracking that grows the string one bracket at a time while
 *   tracking how many '(' (open) and ')' (close) have been placed. Two rules keep
 *   every partial string a valid prefix of some balanced sequence, so no doomed
 *   branch is ever explored: place '(' only while open < n, and place ')' only
 *   while close < open (you can never close more than is currently open). Once the
 *   buffer reaches length 2n it must have open == close == n, i.e. it is a finished
 *   balanced sequence, and it is recorded. Trying '(' before ')' makes the output
 *   come out in the same order as the problem's example.
 *
 * Complexity: O(C(n) * n) time -- C(n) valid sequences, each costing O(n) to copy;
 *   recursion depth is 2n and the reused buffer is O(n) space (output aside).
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    // Extend `current` by one bracket at a time. Invariant at every call:
    // close <= open <= n, so the buffer is always a valid prefix of a balanced
    // string -- an invalid arrangement is never even started.
    void backtrack(int n, int open, int close, string& current,
                   vector<string>& result) {
        if ((int)current.size() == 2 * n) {
            result.push_back(current);          // open == close == n: complete match
            return;
        }
        if (open < n) {                         // still have unopened pairs
            current.push_back('(');
            backtrack(n, open + 1, close, current, result);
            current.pop_back();                 // undo the choice (backtrack)
        }
        if (close < open) {                     // only close a bracket that is open
            current.push_back(')');
            backtrack(n, open, close + 1, current, result);
            current.pop_back();                 // undo the choice (backtrack)
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        current.reserve(2 * n);                 // final length is fixed at 2n
        backtrack(n, 0, 0, current, result);
        return result;
    }
};
