/*
 * LeetCode 1439 - Find the Kth Smallest Sum of a Matrix With Sorted Rows
 *
 * Given an m x n matrix whose every row is sorted in non-decreasing order, pick
 * exactly one element from each row to form an array; its value is the sum of
 * the chosen entries. Among all n^m such arrays, return the k-th smallest sum.
 *
 * Input  : vector<vector<int>> mat (rows sorted ascending), int k.
 * Output : int — the k-th smallest achievable row-pick sum.
 *
 * Constraints: 1 <= m, n <= 40; 1 <= mat[i][j] <= 5000; 1 <= k <= min(200, n^m).
 *   The largest possible sum is 40 * 5000 = 2e5, comfortably within int.
 *
 * Approach: fold the rows one at a time while keeping only the k smallest partial
 *   sums obtainable from the rows processed so far. Begin with the single partial
 *   sum 0. For each new row, add every current partial sum to every element of
 *   the row, sort the results, and truncate to the k smallest.
 *
 *   Keeping just k is provably enough: if a partial sum p is not among the k
 *   smallest for the current prefix, then at least k partial sums are <= p. For
 *   any single way of completing the remaining rows, those k partial sums each
 *   yield a total <= p + (that completion), so p's total can never be smaller
 *   than the k-th — it cannot belong to the global k smallest. Hence discarding
 *   everything past the k-th partial sum at each step is safe. With k <= 200 and
 *   n <= 40, each fold examines at most k * n = 8000 candidates.
 *
 * Complexity: O(m * k * n * log(k * n)) time (each of m folds builds and sorts up
 *   to k * n candidates) and O(k * n) space for the candidate list.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        // best holds the k smallest sums using the rows folded in so far.
        vector<int> best = {0};

        for (const auto& row : mat) {
            vector<int> next;
            next.reserve(best.size() * row.size());
            // Every partial sum can be extended by any element of this row.
            for (int s : best)
                for (int v : row)
                    next.push_back(s + v);

            sort(next.begin(), next.end());
            if ((int)next.size() > k)
                next.resize(k);                // discard all but the k smallest
            best = move(next);
        }

        // After every row is folded, the k-th smallest total sits at index k-1.
        return best[k - 1];
    }
};
