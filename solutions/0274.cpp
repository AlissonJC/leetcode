/*
 * LeetCode 274 - H-Index
 *
 * Given citations[i] = number of citations of the i-th paper, return the researcher's
 * h-index: the largest h such that at least h papers each have >= h citations.
 *
 * Input  : vector<int> citations.
 * Output : the integer h-index.
 *
 * Constraints: 1 <= n == citations.length <= 5000; 0 <= citations[i] <= 1000.
 *
 * Approach: counting sort (bucket count) for O(n). The key observation is that the
 *   h-index can never exceed n, the total number of papers, because you cannot have more
 *   than n papers cited at least h times. So bucket[c] counts papers with exactly c
 *   citations, but every paper with c >= n is dropped into bucket[n] (its exact excess
 *   count is irrelevant once it is already >= n). Then sweep the threshold h from n down
 *   to 0, accumulating papers = number of papers with citation count >= h (adding
 *   bucket[h] at each step, since we descend). The first (hence largest) h for which
 *   papers >= h is the answer; h = 0 always qualifies, so the loop always returns.
 *   This avoids the O(n log n) sort by exploiting the small, bounded key range.
 *
 * Complexity: O(n) time (one pass to bucket, one pass over n+1 buckets), O(n) space for
 *   the bucket array.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = (int)citations.size();

        // bucket[c] = how many papers have exactly c citations, but pile everything with
        // c >= n into bucket[n]: for the h-index those papers are indistinguishable.
        vector<int> bucket(n + 1, 0);
        for (int c : citations)
            bucket[c >= n ? n : c]++;

        // Descend the threshold h; papers accumulates the count with citations >= h.
        int papers = 0;
        for (int h = n; h >= 0; --h) {
            papers += bucket[h];
            if (papers >= h)          // largest h with at least h papers cited >= h times
                return h;
        }
        return 0;                     // unreachable: h = 0 always satisfies papers >= 0
    }
};
