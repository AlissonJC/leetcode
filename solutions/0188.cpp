/*
 * LeetCode 188 - Best Time to Buy and Sell Stock IV
 *
 * Given an array prices (prices[i] is the stock price on day i) and an integer k, find
 * the maximum profit achievable with AT MOST k buy-sell transactions. Transactions may
 * not overlap in time: the stock must be sold before it can be bought again. Doing
 * nothing (profit 0) is always allowed.
 *
 * Input  : int k, vector<int> prices.
 * Output : int — the maximum total profit over at most k transactions.
 *
 * Constraints: 1 <= k <= 100, 1 <= n <= 1000, 0 <= prices[i] <= 1000.
 *
 * Approach: Generalize the two-transaction state machine to k transactions. For each
 *   transaction index t (1..k) keep two running bests as of the current day:
 *     buy[t]  - best profit while holding the t-th stock (its buy was funded by sell[t-1])
 *     sell[t] - best profit after closing the t-th transaction
 *   For every price p, sweep t = 1..k:
 *     buy[t]  = max(buy[t],  sell[t-1] - p)     // open the t-th position, p out of pocket
 *     sell[t] = max(sell[t], buy[t]  + p)       // close it, p back in
 *   with sell[0] = 0. Updating buy[t] then sell[t] within a day only ever lets a buy and
 *   sell resolve on the same day (a 0-profit no-op), so it never inflates the answer. The
 *   result is sell[k]; more transactions subsume fewer.
 *
 *   Shortcut: at most floor(n/2) transactions can ever fit in n days, so once k >= n/2 the
 *   cap is irrelevant and the problem collapses to "unlimited transactions" — greedily bank
 *   every positive day-to-day rise. This also avoids an oversized DP when k is large.
 *
 *   Overflow: profit <= n * maxPrice = 1000 * 1000 = 1e6, well within int. buy[t] starts at
 *   INT_MIN; since p >= 0, buy[t] + p only moves the sentinel toward zero (never overflows),
 *   and it can never win a max against a real sell value.
 *
 * Complexity: O(n * k) time, O(k) space (the unlimited branch is O(n) / O(1)).
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = (int)prices.size();
        if (n < 2 || k == 0) return 0;              // no room (or no allowance) to trade

        // k large enough that the cap can't bind -> unlimited: take every upward step.
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i)
                if (prices[i] > prices[i - 1])
                    profit += prices[i] - prices[i - 1];
            return profit;
        }

        // Bounded k: per-transaction buy/sell states, buys start "impossible", sells at 0.
        vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
        for (int p : prices) {
            for (int t = 1; t <= k; ++t) {
                buy[t]  = max(buy[t],  sell[t - 1] - p);   // fund t-th buy from (t-1) profit
                sell[t] = max(sell[t], buy[t] + p);        // realize t-th sale
            }
        }
        return sell[k];                              // best over using up to k transactions
    }
};
