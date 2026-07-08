/*
 * LeetCode 123 - Best Time to Buy and Sell Stock III
 *
 * Given an array prices where prices[i] is the stock price on day i, find the maximum
 * profit achievable with AT MOST TWO buy-sell transactions. Transactions may not overlap
 * in time: the stock must be sold before it can be bought again. Doing nothing (profit 0)
 * is always allowed.
 *
 * Input  : vector<int> prices.
 * Output : int — the maximum total profit over at most two transactions.
 *
 * Constraints: 1 <= n <= 1e5, 0 <= prices[i] <= 1e5.
 *
 * Approach: A four-state "profit machine" scanned once. As of the current day, track the
 *   best achievable running profit in each of four situations:
 *     buy1  - after buying the 1st stock          (cash flow so far = -buyPrice)
 *     sell1 - after selling the 1st stock
 *     buy2  - after buying the 2nd stock          (started from sell1's profit)
 *     sell2 - after selling the 2nd stock
 *   For each price p update, in this exact order:
 *     buy1  = max(buy1,  -p)          // pay p for the first buy
 *     sell1 = max(sell1, buy1 + p)    // add p when selling the first
 *     buy2  = max(buy2,  sell1 - p)   // spend p on the second buy, on top of sell1
 *     sell2 = max(sell2, buy2 + p)    // add p when selling the second
 *   Updating in this cascade lets a buy and sell resolve on the same day; that only ever
 *   produces a 0-profit step, so it never inflates the answer, and it correctly allows
 *   the second transaction to reuse the day the first one ended. sell1/sell2 start at 0,
 *   so the result is naturally >= 0 (Example 3: strictly falling prices -> 0). The final
 *   answer is sell2, since two transactions subsume one and one subsumes zero.
 *
 *   Overflow note: prices are non-negative, so buy1 + p and buy2 + p only move a sentinel
 *   toward zero (never below INT_MIN), and after day 1 all four states are finite and
 *   bounded by ~2e5. Plain int is safe.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // buy states start at "impossible" (very negative); sell states at 0 (do nothing).
        int buy1 = INT_MIN, sell1 = 0;
        int buy2 = INT_MIN, sell2 = 0;

        for (int p : prices) {
            buy1  = max(buy1,  -p);          // best position holding the 1st stock
            sell1 = max(sell1, buy1 + p);    // best profit after the 1st sale
            buy2  = max(buy2,  sell1 - p);   // best position holding the 2nd stock
            sell2 = max(sell2, buy2 + p);    // best profit after the 2nd sale
        }
        return sell2;                        // >= 0; two transactions cover one and none
    }
};
