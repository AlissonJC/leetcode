/*
 * LeetCode 3754 - Concatenate Non-Zero Digits and Multiply by Sum I
 *
 * Given an integer n, form a new integer x by concatenating all the non-zero digits
 * of n in their original (left-to-right) order; if n has no non-zero digits, x = 0.
 * Let sum be the sum of the digits of x. Return x * sum.
 *
 * Input  : int n. Output : long long — the value of x * sum.
 *
 * Constraints: 0 <= n <= 1e9.
 *
 * Approach: Scan the decimal digits of n from most significant to least significant
 *   (which is exactly what iterating over to_string(n) gives). Drop every zero and
 *   rebuild the surviving digits into x with the usual x = x*10 + d recurrence, which
 *   preserves their original order — the order matters because x's numeric value
 *   depends on it (e.g. 1234 != 4321), whereas sum does not. Accumulate sum as we go,
 *   then multiply. Building x left-to-right is why we read the digits via the string
 *   rather than peeling them off with % 10, which would yield reversed order.
 *
 *   Edge case: n = 0 leaves x = 0 and sum = 0, so the answer is 0, matching the
 *   "no non-zero digits" rule. Every n > 0 has at least one non-zero digit.
 *
 * Overflow: x can reach 999999999 (n = 999999999) with sum = 81, so x * sum is about
 *   8.1e10 — beyond 32-bit int. Both x and sum are held in long long so the product
 *   is computed in 64-bit.
 *
 * Complexity: O(d) time and O(d) space, where d <= 10 is the number of digits of n.
 */

#include <string>
using namespace std;

class Solution {
public:
    long long sumAndMultiply(int n) {
        string s = to_string(n);
        long long x = 0, sum = 0;
        for (char c : s) {
            if (c != '0') {                 // keep only non-zero digits
                int d = c - '0';
                x = x * 10 + d;             // append d, preserving original order
                sum += d;                   // sum of x's digits == sum of these digits
            }
        }
        return x * sum;                     // 64-bit product; 0 when n has no non-zero digit
    }
};
