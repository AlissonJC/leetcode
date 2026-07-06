/*
 * LeetCode 1833 - Maximum Ice Cream Bars
 *
 * A boy has `coins` coins and faces n ice cream bars with prices costs[i]. Bars may be
 * bought in any order; return the maximum number he can afford.
 *
 * Input  : vector<int> costs, int coins.
 * Output : the maximum count of bars purchasable.
 *
 * Constraints: 1 <= n <= 1e5; 1 <= costs[i] <= 1e5; 1 <= coins <= 1e8.
 *
 * Greedy: to maximize the *count* of bars, always buy the cheapest ones first. Exchange
 *   argument: any affordable set of k bars can be swapped for the k globally cheapest
 *   bars without increasing the total cost, so the cheapest-first choice is never worse.
 *
 * Approach: realize the sort with counting sort, since prices lie in the fixed range
 *   [1, 1e5]. Tally count[c] = how many bars cost c, then sweep c upward from 1: at each
 *   price buy as many as the budget allows, affordable = min(count[c], budget / c), add
 *   that to the tally and subtract their cost. Because prices are visited in increasing
 *   order, the moment the budget drops below the current price it is below every remaining
 *   price too, so the loop can stop early. This is O(n + maxCost) with no comparison sort.
 *
 * Overflow note: keep the running budget in a 64-bit integer. Although the final answer
 *   fits in int, the product affordable * c can reach 1e5 * 1e5 = 1e10 in intermediate
 *   reasoning; computing it as long long removes any 32-bit overflow risk.
 *
 * Complexity: O(n + maxCost) time, O(maxCost) space for the counts.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        const int MAXC = 100000;
        vector<int> count(MAXC + 1, 0);      // count[c] = number of bars priced c
        int maxCost = 0;
        for (int c : costs) {
            count[c]++;
            maxCost = max(maxCost, c);
        }

        long long budget = coins;            // up to 1e8; 64-bit keeps products safe
        int bars = 0;
        for (int c = 1; c <= maxCost; ++c) {
            if (budget < c)
                break;                       // cheapest remaining bar already unaffordable
            if (count[c] == 0)
                continue;
            // Buy as many bars of this price as the budget permits.
            int affordable = (int)min<long long>(count[c], budget / c);
            bars += affordable;
            budget -= (long long)affordable * c;
        }
        return bars;
    }
};
