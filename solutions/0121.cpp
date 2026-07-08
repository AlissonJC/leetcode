/*
 * LeetCode 121 - Best Time to Buy and Sell Stock
 *
 * Given an array prices where prices[i] is the stock price on day i, buy on one day and
 * sell on a strictly later day to maximize profit. Return the best achievable profit, or
 * 0 if no profitable buy/sell pair exists (a single transaction, or none).
 *
 * Input  : vector<int> prices.
 * Output : int — the maximum profit from one buy-then-sell, else 0.
 *
 * Constraints: 1 <= n <= 1e5, 0 <= prices[i] <= 1e4.
 *
 * Approach: One pass. The best profit that sells on day i is prices[i] minus the cheapest
 *   price seen on any earlier day, so track the running minimum and, at each day, update
 *   the answer with (today's price - minSoFar). Because the minimum only ever looks
 *   backward, the "buy before sell" order is respected automatically. Starting the answer
 *   at 0 covers the "no profit" case (Example 2, monotically falling prices).
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minSoFar = prices[0];            // cheapest buy price among days seen so far
        int best = 0;                        // no transaction yields 0

        for (int p : prices) {
            best = max(best, p - minSoFar);  // sell today against the cheapest earlier day
            minSoFar = min(minSoFar, p);     // then let today be a future buy candidate
        }
        return best;
    }
};
