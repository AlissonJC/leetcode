/*
 * LeetCode 1090 - Largest Values From Labels
 *
 * Each of n items has a value and a label. Choose a subset of items maximizing the sum
 * of their values, subject to two caps: at most numWanted items in total, and at most
 * useLimit items sharing any single label. Return that maximum sum.
 *
 * Input  : vector<int> values, vector<int> labels (same length n), int numWanted,
 *          int useLimit.
 * Output : int — the maximum achievable sum of chosen values.
 *
 * Constraints: 1 <= n <= 2e4, 0 <= values[i], labels[i] <= 2e4, 1 <= numWanted,
 *   useLimit <= n.
 *
 * Approach: Greedy by value. Sort items in descending value order and sweep once,
 *   keeping a per-label tally of how many have been picked. Take the current item iff
 *   its label still has room (tally < useLimit) and the overall budget still has room
 *   (picked < numWanted); stop once numWanted items are chosen. Picking the largest
 *   still-legal value at each step is optimal: this is the intersection of a uniform
 *   matroid (total count) and a partition matroid (per label), and greedily taking the
 *   heaviest feasible element is optimal for such structures. Exchange view: if an
 *   optimum ever skipped an available larger value for a smaller one under the same
 *   caps, swapping them would not decrease the sum and keeps every constraint satisfied.
 *
 *   Note: the answer may use FEWER than numWanted items when label caps run out first
 *   (see example 3) — the total cap is an upper bound, not a quota.
 *
 * Complexity: O(n log n) for the sort (dominant), O(n) sweep; O(n) space.
 */

#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = (int)values.size();

        // Pair each value with its label so sorting keeps them together.
        vector<pair<int, int>> items(n);            // (value, label)
        for (int i = 0; i < n; ++i)
            items[i] = {values[i], labels[i]};
        sort(items.begin(), items.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.first > b.first;           // descending by value
             });

        unordered_map<int, int> used;               // label -> count already taken
        long long total = 0;                         // sum fits in int (<= 4e8) but keep it wide
        int taken = 0;

        for (const auto& [val, lab] : items) {
            if (taken >= numWanted) break;          // global budget spent -> nothing more helps
            if (used[lab] >= useLimit) continue;    // this label is full; skip and keep scanning
            total += val;                           // commit the largest still-legal value
            ++used[lab];
            ++taken;
        }
        return (int)total;
    }
};
