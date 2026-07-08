/*
 * LeetCode 122 - Best Time to Buy and Sell Stock II
 *
 * Given an array prices where prices[i] is the stock price on day i, maximize profit with
 * UNLIMITED transactions while holding at most one share at any time (you may sell and
 * rebuy on the same day). Return the maximum total profit.
 *
 * Input  : vector<int> prices.
 * Output : int — the maximum total profit over any number of non-overlapping transactions.
 *
 * Constraints: 1 <= n <= 3e4, 0 <= prices[i] <= 1e4.
 *
 * Approach: Greedy — add up every positive day-to-day rise. Any profitable buy-low/sell-high
 *   spanning several days telescopes into the sum of its consecutive daily gains, so banking
 *   each positive prices[i]-prices[i-1] captures the total of all upward moves and ignores
 *   every downward move. That is exactly optimal: no schedule can collect more than the sum
 *   of all rises, and this one collects all of them (equivalent to buying at each local
 *   minimum and selling at each local maximum). Falling prices contribute nothing, giving 0
 *   when prices never rise.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        for (size_t i = 1; i < prices.size(); ++i)
            if (prices[i] > prices[i - 1])           // only upward steps are worth capturing
                profit += prices[i] - prices[i - 1]; // telescopes to every valley->peak gain
        return profit;
    }
};
