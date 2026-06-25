/*
 * LeetCode 28 - Find the Index of the First Occurrence in a String
 *
 * Return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not a substring of haystack.
 *
 * Input  : strings haystack, needle (lowercase letters).
 * Output : the starting index of the first match, or -1.
 * Constraints: 1 <= haystack.length, needle.length <= 1e4.
 *
 * Approach: slide the needle across the haystack. For every start position i
 *   that still leaves room for needle (i + m <= n), compare characters until a
 *   mismatch or until all m match; a full match means needle starts at i. With
 *   the early break on the first mismatch this naive scan is well within the
 *   limits for strings up to 1e4.
 *
 * Complexity: O(n * m) worst case, O(1) extra space (n, m are the lengths).
 */

#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = (int)haystack.size(), m = (int)needle.size();
        for (int i = 0; i + m <= n; ++i) {      // only starts where needle can still fit
            int j = 0;
            while (j < m && haystack[i + j] == needle[j]) ++j;  // match run from i
            if (j == m) return i;               // matched the whole needle
        }
        return -1;                              // never found
    }
};
