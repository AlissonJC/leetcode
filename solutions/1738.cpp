/*
 * LeetCode 1738 - Find Kth Largest XOR Coordinate Value
 *
 * For a matrix of non-negative integers, the value of coordinate (a, b) is the XOR of
 * every matrix[i][j] with 0 <= i <= a and 0 <= j <= b (a 2D prefix XOR). Among all m*n
 * coordinate values, return the k-th largest (1-indexed).
 *
 * Input  : vector<vector<int>> matrix (m x n); int k. Output : int — k-th largest value.
 *
 * Constraints: 1 <= m, n <= 1000; 0 <= matrix[i][j] <= 1e6; 1 <= k <= m*n. Each value is
 *   an XOR of numbers below 2^20, so it stays below 2^20 and fits in a 32-bit int.
 *
 * Approach: build the 2D prefix XOR. Just as a 2D prefix sum is
 *   P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + a[i-1][j-1], the XOR version replaces
 *   every operation by XOR (and the subtraction of the doubly-counted corner becomes an
 *   XOR, since XOR is its own inverse):
 *     P[i][j] = P[i-1][j] ^ P[i][j-1] ^ P[i-1][j-1] ^ matrix[i-1][j-1].
 *   Each P[i][j] is exactly one coordinate value, so collect all m*n of them and pick the
 *   k-th largest with a selection (nth_element) rather than a full sort. Only the previous
 *   prefix row is needed at a time, so the prefix grid is kept in O(n) memory.
 *
 * Complexity: O(m*n) time (prefix build + average-linear selection); O(m*n) space for the
 *   list of values, plus O(n) for the rolling prefix rows.
 */

#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();

        vector<int> prev(n + 1, 0), cur(n + 1, 0);   // prefix rows i-1 and i
        vector<int> vals;
        vals.reserve((size_t)m * n);

        for (int i = 1; i <= m; ++i) {
            cur[0] = 0;                              // empty column prefix is 0
            for (int j = 1; j <= n; ++j) {
                // 2D prefix XOR: top ^ left ^ corner (cancels the double count) ^ cell.
                cur[j] = prev[j] ^ cur[j - 1] ^ prev[j - 1] ^ matrix[i - 1][j - 1];
                vals.push_back(cur[j]);
            }
            swap(prev, cur);                         // current row becomes "previous"
        }

        // k-th largest = the element that belongs at index k-1 when sorted descending.
        nth_element(vals.begin(), vals.begin() + (k - 1), vals.end(), greater<int>());
        return vals[k - 1];
    }
};
