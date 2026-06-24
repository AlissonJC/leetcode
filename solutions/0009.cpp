/*
 * LeetCode 9 - Palindrome Number
 *
 * Return true if the integer x reads the same forwards and backwards.
 *
 * Input  : int x.   Output: bool.
 * Constraints: -2^31 <= x <= 2^31 - 1.
 *
 * Approach: a negative number is never a palindrome (the leading '-' has no
 *   trailing match), and any nonzero multiple of 10 ends in 0 but cannot start
 *   with 0, so it fails too. Otherwise reverse only the lower half of the
 *   digits: repeatedly peel the last digit of x onto rev until rev has caught up
 *   (x <= rev). For an even digit count the halves match when x == rev; for an
 *   odd count the middle digit sits in rev, so x == rev / 10. Reversing just
 *   half keeps rev within int range, so no overflow and no string conversion.
 *
 * Complexity: O(log10(x)) time, O(1) space.
 */

class Solution {
public:
    bool isPalindrome(int x) {
        // Negatives, and trailing-zero numbers other than 0 itself, are not palindromes.
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;

        int rev = 0;
        while (x > rev) {           // stop once rev holds the upper half of the digits
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        // Even length: x == rev. Odd length: drop rev's middle digit with rev/10.
        return x == rev || x == rev / 10;
    }
};
