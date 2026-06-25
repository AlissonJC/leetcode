/*
 * LeetCode 67 - Add Binary
 *
 * Given two binary strings a and b, return their sum as a binary string.
 *
 * Input  : strings a, b (characters '0'/'1', no leading zeros except "0").
 * Output : the binary representation of a + b.
 * Constraints: 1 <= a.length, b.length <= 1e4.
 *
 * Approach: add the strings column by column from the least significant bit, the
 *   same as grade-school addition. At each position sum the carry plus the two
 *   current bits (0 when a string is exhausted); the output bit is sum & 1 and
 *   the new carry is sum >> 1. Continue while either string has bits left or a
 *   carry remains, then reverse the digits collected (they were produced least
 *   significant first).
 *
 * Complexity: O(max(m, n)) time, O(max(m, n)) for the result.
 */

#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';     // add a's current bit, move left
            if (j >= 0) sum += b[j--] - '0';     // add b's current bit, move left
            result.push_back(char('0' + (sum & 1)));  // low bit of the column sum
            carry = sum >> 1;                    // high bit carries to the next column
        }
        reverse(result.begin(), result.end());   // built LSB-first, flip to normal order
        return result;
    }
};
