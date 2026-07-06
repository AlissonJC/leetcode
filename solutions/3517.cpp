/*
 * LeetCode 3517 - Smallest Palindromic Rearrangement I
 *
 * Given a string s that is guaranteed to be a palindrome, return the lexicographically
 * smallest string that can be formed by rearranging s and is itself a palindrome.
 *
 * Input  : string s (already a palindrome).
 * Output : the lexicographically smallest palindromic permutation of s.
 *
 * Constraints: 1 <= s.length <= 1e5; s consists of lowercase English letters; s is
 *   palindromic (so at most one letter has an odd frequency).
 *
 * Approach: a palindrome is fully determined by its first half plus, for odd length, one
 *   forced middle character. Two palindromic permutations differ first inside that first
 *   half (the middle is forced to be the single odd-frequency letter), and the palindrome
 *   string is prefixed by its first half — so the lexicographically smallest palindrome is
 *   the one whose first half is smallest, i.e. the half-multiset written in ascending
 *   order. Count the 26 letter frequencies, emit floor(count/2) copies of each letter from
 *   'a' to 'z' to form that sorted half (this is the counting-sort step), place the lone
 *   odd letter in the middle when the length is odd, and mirror the half to finish.
 *
 * Complexity: O(n + 26) time, O(n) space for the output.
 */

#include <string>
using namespace std;

class Solution {
public:
    string smallestPalindrome(string s) {
        int freq[26] = {0};
        for (char c : s)
            freq[c - 'a']++;

        // Build the smallest first half: each letter floor(count/2) times, ascending.
        // Emitting letters in order 'a'..'z' is a counting sort of the half-multiset.
        string half;
        half.reserve(s.size() / 2);
        char mid = 0;
        bool hasMid = false;
        for (int i = 0; i < 26; ++i) {
            half.append(freq[i] / 2, char('a' + i));
            if (freq[i] & 1) {           // the (at most one) odd-frequency letter
                mid = char('a' + i);
                hasMid = true;
            }
        }

        // Assemble half + optional forced middle + mirrored half.
        string result = half;
        if (hasMid)
            result += mid;               // middle exists only for odd-length palindromes
        result.append(half.rbegin(), half.rend());
        return result;
    }
};
