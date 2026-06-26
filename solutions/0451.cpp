/*
 * LeetCode 451 - Sort Characters By Frequency
 *
 * Given a string s, rearrange its characters so that they appear in decreasing
 * order of frequency, with all copies of the same character kept together. Any
 * valid ordering among equally frequent characters is accepted.
 *
 * Input  : string s.
 * Output : string — s reordered by descending character frequency.
 *
 * Constraints: 1 <= s.length <= 5*10^5; s holds upper/lowercase English letters
 *              and digits (all within ASCII 0..127).
 *
 * Approach: count-then-bucket, the same O(n) idea as Top-K-Frequent, which avoids
 *   the O(n log n) of sorting characters. First tally every character in a fixed
 *   128-slot table (the charset is letters and digits). A character's frequency is
 *   in 1..n, so index buckets directly by frequency: bucket[f] lists the characters
 *   that occur exactly f times. Finally sweep f from n down to 1 and, for each
 *   character in that bucket, append it f times — descending frequency, with equal
 *   characters naturally contiguous.
 *
 * Complexity: O(n) time (counting is O(n), the bucket sweep emits exactly n
 *   characters) and O(n) space for the buckets and output.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        int n = (int)s.size();

        // Frequency of each character; 128 slots cover all letters and digits.
        int count[128] = {0};
        for (unsigned char c : s) ++count[c];   // unsigned char -> safe 0..127 index

        // bucket[f] = characters appearing exactly f times (f ranges 1..n).
        vector<vector<char>> bucket(n + 1);
        for (int c = 0; c < 128; ++c)
            if (count[c] > 0) bucket[count[c]].push_back((char)c);

        // Highest frequency first; emit each character f times so duplicates group.
        string result;
        result.reserve(n);
        for (int f = n; f >= 1; --f)
            for (char c : bucket[f])
                result.append(f, c);            // f copies of character c
        return result;
    }
};
