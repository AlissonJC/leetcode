/*
 * LeetCode 2144 - Minimum Cost of Buying Candies With Discount
 *
 * A shop gives a free candy for every two bought, where the free candy must cost
 * at most the cheaper of the two purchased. Given the candy costs, return the
 * minimum total cost to obtain all candies.
 *
 * Input  : vector<int> cost.   Output: minimum total cost (int).
 * Constraints: 1 <= cost.length <= 100, 1 <= cost[i] <= 100.
 *
 * Approach: greedy. Sort the costs in descending order and process them in
 *   triples. Within each triple the two most expensive are paid for and the
 *   third (the cheapest, which is <= the other two, so a valid free pick) is
 *   taken for free. Pairing the most expensive candies together and freeing the
 *   next one maximizes the discount, so sum every cost except those at positions
 *   i where i % 3 == 2. Leftover candies that don't complete a triple are paid.
 *
 * Complexity: O(n log n) time (the sort), O(1) extra space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.rbegin(), cost.rend());          // descending: biggest first
        int total = 0;
        for (int i = 0; i < (int)cost.size(); ++i)
            if (i % 3 != 2) total += cost[i];       // every 3rd candy is the free one
        return total;
    }
};
