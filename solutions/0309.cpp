/*
 * LeetCode 309 - Best Time to Buy and Sell Stock with Cooldown
 *
 * Given an array prices where prices[i] is the stock price on day i, maximize profit with
 * UNLIMITED transactions (hold at most one share) subject to one rule: the day immediately
 * after a sale is a mandatory cooldown on which you may not buy. Return the maximum profit.
 *
 * Input  : vector<int> prices.
 * Output : int — the maximum total profit under the cooldown rule.
 *
 * Constraints: 1 <= n <= 5000, 0 <= prices[i] <= 1000.
 *
 * Approach: A three-state machine over the days. As of the current day track the best
 *   running profit in each situation:
 *     hold - currently holding a share
 *     sold - sold today (so the NEXT day is a forced cooldown)
 *     rest - idle and free to buy (not holding, not just-sold)
 *   For each price p, using yesterday's values:
 *     sold = hold + p                 // sell what was held yesterday
 *     hold = max(hold, rest - p)      // keep holding, or buy today (only from 'rest')
 *     rest = max(rest, prevSold)      // stay idle, or finish a cooldown from yesterday's sale
 *   The cooldown falls out naturally: buying reads 'rest', and 'rest' only ever absorbs the
 *   'sold' value from the PREVIOUS day (prevSold), so a share sold on day d cannot be
 *   rebought until day d+2. The best final position is max(sold, rest); ending while still
 *   holding is never better than having sold.
 *
 *   Sentinel: 'hold' starts at a large negative so "holding before any purchase" can never
 *   win a max; hold + p stays deeply negative (no overflow) until a real buy occurs.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int NEG = -1000000000;         // below any real profit; NEG + p never overflows
        int hold = NEG, sold = 0, rest = 0;

        for (int p : prices) {
            int prevSold = sold;             // yesterday's "just sold" — the only sale rest may absorb today
            sold = hold + p;                 // sell today the share held as of yesterday
            hold = max(hold, rest - p);      // hold on, or buy today out of an idle (non-cooldown) state
            rest = max(rest, prevSold);      // stay idle, or come off yesterday's sale into free state
        }
        return max(sold, rest);              // never advantageous to end still holding
    }
};
