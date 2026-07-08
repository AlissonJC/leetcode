/*
 * LeetCode 2813 - Maximum Elegance of a K-Length Subsequence
 *
 * Each item is [profit, category]. The elegance of a chosen subsequence is
 * total_profit + (distinct_categories)^2, where total_profit sums the chosen profits and
 * distinct_categories counts how many different categories appear. Choose exactly k items
 * to maximize elegance, and return that maximum.
 *
 * Input  : vector<vector<int>> items (each {profit, category}), int k.
 * Output : long long — the maximum elegance over all size-k subsequences.
 *
 * Constraints: 1 <= n <= 1e5, 1 <= profit <= 1e9, 1 <= category <= n, 1 <= k <= n.
 *
 * Approach: Greedy in two phases. First sort items by profit descending and take the top k;
 *   this maximizes the profit term outright. While taking them, remember which categories are
 *   present and push onto a stack the profits of items whose category was ALREADY present —
 *   these are "redundant": removing one does not lower the distinct count. Record the elegance
 *   of this initial pick. Then walk the remaining items (still in descending profit). For each
 *   item with a NEW category, trade it in for the cheapest redundant item: pop the stack top
 *   (the smallest redundant profit, since duplicates were pushed in descending order), which
 *   loses the least profit while keeping size k and raising the distinct count by one. Update
 *   the answer after every trade. Stop as soon as the stack is empty: then all selected items
 *   already have distinct categories (count == k, the maximum), so the squared term can grow
 *   no further and remaining profits are only smaller.
 *
 * Overflow: profit sum reaches k * 1e9 <= 1e14 and distinct^2 <= (1e5)^2 = 1e10, so every
 *   running total is 64-bit.
 *
 * Complexity: O(n log n) time (dominated by the sort), O(n) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        int n = (int)items.size();

        // Highest profits first — greedily fill the profit term.
        sort(items.begin(), items.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] > b[0]; });

        vector<char> present(n + 1, 0);   // is a category currently in the selection?
        vector<int> redundant;            // profits of duplicate-category picks, ascending toward the back
        long long sum = 0;
        long long distinct = 0;

        // Phase 1: take the top k items.
        for (int i = 0; i < k; ++i) {
            int p = items[i][0], c = items[i][1];
            sum += p;
            if (!present[c]) { present[c] = 1; ++distinct; }
            else redundant.push_back(p);  // its category is covered elsewhere -> safe to drop later
        }
        long long ans = sum + distinct * distinct;

        // Phase 2: trade cheapest redundant items for fresh categories.
        for (int i = k; i < n; ++i) {
            int p = items[i][0], c = items[i][1];
            if (present[c]) continue;           // category already covered; lower profit -> no gain
            if (redundant.empty()) break;       // no slack to trade; distinct is already maxed at k
            sum += p - redundant.back();        // add new profit, drop the smallest redundant one
            redundant.pop_back();
            present[c] = 1;
            ++distinct;
            ans = max(ans, sum + distinct * distinct);
        }
        return ans;
    }
};
