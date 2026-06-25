/*
 * LeetCode 17 - Letter Combinations of a Phone Number
 *
 * Given a string of digits from 2-9, return every letter combination the number
 * could spell on a telephone keypad, where 2->abc, 3->def, 4->ghi, 5->jkl,
 * 6->mno, 7->pqrs, 8->tuv, 9->wxyz (1 maps to nothing). The combinations may be
 * returned in any order; an empty input yields an empty list.
 *
 * Input  : string digits. Output : vector<string> of all combinations.
 *
 * Constraints: 0 <= digits.length <= 4; each digit is in ['2','9']. At most
 *   4^4 = 256 combinations are produced.
 *
 * Approach: backtracking. Each digit maps to a group of candidate letters, and a
 *   combination is built one digit at a time. At position pos, append each letter
 *   of that digit's group, recurse to pos+1, then pop the letter to restore the
 *   state before trying the next one. When pos reaches the end of the string the
 *   current buffer is a finished combination and is recorded. The recursion tree
 *   has one level per digit and branches by that digit's letter count, so it
 *   walks exactly the cross product of the letter groups.
 *
 * Complexity: O(4^L * L) time, where L = digits.length and each digit owns up to
 *   4 letters (4^L leaves, each costing O(L) to copy); O(L) recursion depth.
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    // Keypad letters indexed by digit value; 0 and 1 contribute nothing.
    static constexpr const char* MAPPING[10] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(const string& digits, int pos, string& current,
                   vector<string>& result) {
        if (pos == (int)digits.size()) {
            result.push_back(current);          // a full-length choice is complete
            return;
        }
        // Try every letter mapped to the current digit, restoring state after each.
        for (const char* p = MAPPING[digits[pos] - '0']; *p; ++p) {
            current.push_back(*p);
            backtrack(digits, pos + 1, current, result);
            current.pop_back();                 // undo the choice (backtrack)
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};          // no digits -> no combinations

        vector<string> result;
        string current;
        current.reserve(digits.size());
        backtrack(digits, 0, current, result);
        return result;
    }
};
