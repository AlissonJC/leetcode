/*
 * LeetCode 66 - Plus One
 *
 * A non-negative integer (no leading zeros) is given as a digit array, most
 * significant digit first. Add one to it and return the resulting digit array.
 *
 * Input  : vector<int> digits (each 0..9, most significant first).
 * Output : the digits of the value + 1.
 * Constraints: 1 <= digits.length <= 100, 0 <= digits[i] <= 9.
 *
 * Approach: simulate grade-school increment from the least significant digit.
 *   A digit below 9 just gets +1 and we are done (no further carry). A 9 becomes
 *   0 and the carry continues left. If every digit was 9 the loop falls through,
 *   meaning the number was all nines (e.g. 999), so the answer is a leading 1
 *   followed by the now-zeroed digits.
 *
 * Complexity: O(n) time; O(n) output (O(1) extra besides the all-nines insert).
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            if (digits[i] < 9) {            // no carry needed: increment and finish
                ++digits[i];
                return digits;
            }
            digits[i] = 0;                  // 9 + 1 = 10: write 0, carry to the left
        }
        digits.insert(digits.begin(), 1);   // all nines -> one extra leading digit
        return digits;
    }
};
