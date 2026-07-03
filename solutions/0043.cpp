/*
 * LeetCode 43 - Multiply Strings
 *
 * Given two non-negative integers num1 and num2 represented as decimal
 * strings, return their product, also as a decimal string. The numbers may be
 * up to 200 digits long, so they cannot be parsed into any native integer type
 * (not even 64-bit) - the multiplication must be done by hand, digit by digit.
 *
 * Input  : string num1, string num2 - non-negative integers, digits only, no
 *          leading zeros except the literal "0".
 * Output : string - the product num1 * num2, with no leading zeros.
 *
 * Constraints: 1 <= num1.length, num2.length <= 200; both consist of digits
 *   only; neither has a leading zero except the number 0 itself.
 *
 * Approach: reproduce grade-school long multiplication on digit arrays. The
 *   product of an m-digit number and an n-digit number never exceeds m + n
 *   digits, so allocate that many slots (index 0 = most significant). For each
 *   pair of digits num1[i] and num2[j], their product contributes to exactly
 *   two slots: i + j + 1 is its units place (there are (m-1-i) + (n-1-j) digits
 *   to the right of it) and i + j is where its carry lands. Fold each pairwise
 *   product into the units slot, keep the low digit, and push the carry one
 *   slot to the left. Finally read the slots left to right, dropping the single
 *   possible leading zero. Because 200 x 200 digits is at most 40000 cheap
 *   digit multiplications, this comfortably fits the limits.
 *
 * Complexity: O(m * n) time - every digit of num1 meets every digit of num2
 *   once; O(m + n) space for the result buffer.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        // Zero shortcut: if either factor is "0" the product is "0". Handling
        // it up front also guarantees the leading-zero stripping below never
        // collapses the answer to an empty string.
        if (num1 == "0" || num2 == "0") return "0";

        int m = (int)num1.size(), n = (int)num2.size();

        // pos[k] holds the k-th digit of the product counting from the left.
        // m + n slots always suffice for the product's width.
        vector<int> pos(m + n, 0);

        // Multiply each digit of num1 by each digit of num2, right to left, so
        // carries flow naturally toward the more significant slots.
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j;        // carry slot (more significant)
                int p2 = i + j + 1;    // units slot for this partial product

                // Add into the units slot whatever carry already accumulated
                // there, then split into kept-digit and outgoing-carry. Every
                // quantity here stays comfortably below 100, so plain int holds
                // it with no risk of overflow.
                int sum = mul + pos[p2];
                pos[p2] = sum % 10;    // low digit stays in place
                pos[p1] += sum / 10;   // carry moves one slot left
            }
        }

        // Emit digits left to right. At most one leading zero can survive (when
        // the top two source digits multiply without producing a carry), so
        // skip zeros until the first significant digit. The all-zero product
        // was already returned above, so `result` ends up non-empty.
        string result;
        for (int digit : pos) {
            if (result.empty() && digit == 0) continue;
            result.push_back((char)('0' + digit));
        }
        return result;
    }
};
