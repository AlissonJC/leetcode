/*
 * LeetCode 74 - Search a 2D Matrix
 *
 * Given an m x n integer matrix where each row is sorted in non-decreasing order and
 * the first value of every row is greater than the last value of the previous row,
 * determine whether a given target appears in the matrix. The solution must run in
 * O(log(m * n)) time.
 *
 * Input  : vector<vector<int>>& matrix, int target. Output : bool — is target present.
 *
 * Constraints: 1 <= m, n <= 100; -10^4 <= matrix[i][j], target <= 10^4.
 *
 * Approach: The two ordering properties together mean that reading the matrix row by
 *   row yields a single fully sorted sequence: within a row values only increase, and
 *   crossing to the next row also only increases (its first value beats the previous
 *   row's last). So treat the grid as a virtual sorted array of length m*n and binary
 *   search it. A flat index k maps to cell (k / n, k % n), letting each probe read the
 *   right element in O(1) without ever materializing the flattened array. This gives
 *   the required O(log(m*n)) time.
 *
 * Complexity: O(log(m * n)) time, O(1) space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        int lo = 0, hi = m * n - 1;          // inclusive bounds over the virtual sorted array

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;     // lo + (hi-lo)/2 avoids any overflow risk
            int val = matrix[mid / n][mid % n];   // map flat index -> (row, col)
            if (val == target) {
                return true;
            } else if (val < target) {
                lo = mid + 1;                 // target is in the upper half
            } else {
                hi = mid - 1;                 // target is in the lower half
            }
        }
        return false;                         // lo crossed hi: target absent
    }
};
