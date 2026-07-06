/*
 * LeetCode 1051 - Height Checker
 *
 * Students should stand in non-decreasing height order. Given the current line heights,
 * count how many positions hold the wrong student, i.e. how many indices i satisfy
 * heights[i] != expected[i], where expected is heights sorted ascending.
 *
 * Input  : vector<int> heights.
 * Output : the number of out-of-place indices.
 *
 * Constraints: 1 <= heights.length <= 100; 1 <= heights[i] <= 100.
 *
 * Approach: the "expected" line is just heights sorted, so the answer is the count of
 *   positions where the original array differs from its sorted form. Because heights lie
 *   in the tiny fixed range [1, 100], build that sorted order with counting sort instead
 *   of a comparison sort: tally each height's frequency, then sweep values 1..100 and
 *   re-emit each value freq[value] times. The k-th value emitted is exactly expected[k],
 *   so compare it against heights[k] on the fly and increment the mismatch counter.
 *
 * Complexity: O(n + V) time where V = 100 is the height range, O(V) extra space — no
 *   comparison sort needed.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int heightChecker(vector<int>& heights) {
        const int MAXH = 100;
        int freq[MAXH + 1] = {0};        // freq[h] = number of students of height h (1..100)
        for (int h : heights)
            freq[h]++;

        int mismatches = 0;
        int i = 0;                       // position in the original array being checked
        // Walk heights in sorted order; the value emitted at position i is expected[i].
        for (int v = 1; v <= MAXH; ++v) {
            for (int k = 0; k < freq[v]; ++k) {
                if (heights[i] != v)     // this student is not who the sorted line expects
                    ++mismatches;
                ++i;
            }
        }
        return mismatches;
    }
};
