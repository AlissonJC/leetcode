/*
 * LeetCode 857 - Minimum Cost to Hire K Workers
 *
 * There are n workers; worker i has quality[i] and a minimum wage expectation wage[i].
 * Hire exactly k workers as a group paid under two rules: (1) everyone is paid at least
 * their minimum wage, and (2) pay is proportional to quality (double the quality => double
 * the pay). Return the least total money to form such a group; answers within 1e-5 are ok.
 *
 * Input  : vector<int> quality, vector<int> wage, int k.
 * Output : double — the minimum total payment for some valid group of k workers.
 *
 * Constraints: 1 <= k <= n <= 1e4, 1 <= quality[i], wage[i] <= 1e4.
 *
 * Approach: Proportional pay means a single group-wide rate r (money per unit quality):
 *   worker i earns r * quality[i], which must be >= wage[i], i.e. r >= wage[i]/quality[i].
 *   So a group's rate is forced to r = max over the group of ratio[i] = wage[i]/quality[i],
 *   and its total cost is r * (sum of the group's qualities). To minimize, sort workers by
 *   ratio ascending and sweep: the current worker's ratio is the largest seen so far, hence
 *   the rate if this worker is the group's "captain". Among all workers with ratio <= this
 *   one, pick the k with the SMALLEST qualities (that minimizes sum-of-quality for this rate)
 *   using a max-heap that evicts the largest quality once the heap exceeds size k. Whenever
 *   the heap holds exactly k, cost = ratio * sumQ is a candidate; keep the minimum.
 *
 * Overflow/precision: sumQ (<= k * 1e4 <= 1e8) is kept in 64-bit; cost = ratio * sumQ is a
 *   double. Ratios compare cleanly as doubles for these magnitudes, well inside the 1e-5
 *   tolerance.
 *
 * Complexity: O(n log n) time (sort + heap ops), O(n) space.
 */

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = (int)quality.size();

        // Pair each worker with its required rate (wage/quality) and quality; sort by rate.
        vector<pair<double, int>> workers(n);
        for (int i = 0; i < n; ++i)
            workers[i] = {(double)wage[i] / quality[i], quality[i]};
        sort(workers.begin(), workers.end());          // ascending by ratio

        priority_queue<int> maxHeap;                    // qualities of the current candidate set
        long long sumQ = 0;                             // sum of qualities currently in the heap
        double ans = 1e18;

        for (const auto& [ratio, q] : workers) {
            maxHeap.push(q);                            // consider this worker (ratio is the new max)
            sumQ += q;
            if ((int)maxHeap.size() > k) {              // keep only the k smallest qualities
                sumQ -= maxHeap.top();                  // drop the largest quality
                maxHeap.pop();
            }
            if ((int)maxHeap.size() == k)               // 'ratio' is the group's rate (max so far)
                ans = min(ans, ratio * (double)sumQ);
        }
        return ans;
    }
};
