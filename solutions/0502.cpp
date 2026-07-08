/*
 * LeetCode 502 - IPO
 *
 * You start with w capital and may complete at most k distinct projects. Project i needs
 * capital[i] on hand to start and yields a non-negative pure profit profits[i] that is
 * added to your capital on completion. Each project can be done at most once. Choose up to
 * k projects to maximize, and return, your final capital.
 *
 * Input  : int k, int w, vector<int> profits, vector<int> capital (profits/capital len n).
 * Output : int — the maximum final capital after doing at most k projects.
 *
 * Constraints: 1 <= k <= 1e5, 0 <= w <= 1e9, 1 <= n <= 1e5, 0 <= profits[i] <= 1e4,
 *   0 <= capital[i] <= 1e9. The final answer fits in a signed 32-bit integer.
 *
 * Approach: Greedy with a heap. Sort projects by their capital requirement ascending. Run
 *   up to k rounds; in each round first "unlock" every project whose capital requirement is
 *   now <= current capital by pushing its profit into a max-heap, then complete the
 *   available project with the LARGEST profit (pop the heap) and add it to capital. Taking
 *   the most profitable affordable project each round is optimal: profits are non-negative,
 *   so completing a project never lowers capital and can only unlock more projects later —
 *   grabbing the biggest profit now dominates any alternative (exchange argument). Stop
 *   early if no project is affordable.
 *
 * Overflow: capital can climb to w + k*maxProfit ~ 1e9 + 1e9, so keep it in 64-bit while
 *   accumulating even though the guaranteed final value fits in int; capital[i] (<= 1e9)
 *   compares cleanly against it.
 *
 * Complexity: O((n + k) log n) time — each project is pushed/popped at most once and there
 *   are up to k rounds; O(n) space.
 */

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = (int)profits.size();

        // Pair (capital needed, profit) and sort so cheaper-to-start projects come first.
        vector<pair<int, int>> proj(n);
        for (int i = 0; i < n; ++i)
            proj[i] = {capital[i], profits[i]};
        sort(proj.begin(), proj.end());          // ascending by capital requirement

        priority_queue<int> available;           // profits of currently affordable projects
        long long cap = w;
        int idx = 0;                             // next project not yet unlocked

        for (int t = 0; t < k; ++t) {
            // Unlock everything affordable at the current capital (sorted, so a prefix).
            while (idx < n && proj[idx].first <= cap) {
                available.push(proj[idx].second);
                ++idx;
            }
            if (available.empty()) break;        // nothing left we can start -> done
            cap += available.top();              // take the most profitable affordable project
            available.pop();
        }
        return (int)cap;
    }
};
