/*
 * LeetCode 3861 - Minimum Capacity Box
 *
 * capacity[i] is the capacity of the i-th box, and a box can store the item when
 * capacity[i] >= itemSize. Return the index of the box with the minimum capacity
 * that can still store the item; if several boxes tie on that minimum capacity,
 * return the smallest index. If no box can store the item, return -1.
 *
 * Input  : vector<int> capacity, int itemSize. Output : int — the chosen index, or -1.
 *
 * Constraints: 1 <= capacity.length <= 100; 1 <= capacity[i] <= 100;
 *              1 <= itemSize <= 100.
 *
 * Approach: a single linear pass. Track the smallest capacity seen so far that is
 *   still large enough to hold the item, together with its index. Update only on
 *   a strictly smaller fitting capacity, which naturally keeps the earliest index
 *   when several boxes share that minimum. If nothing ever qualifies, the index
 *   stays at its -1 sentinel.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumIndex(vector<int>& capacity, int itemSize) {
        int bestIdx = -1;            // -1 until a box that fits is found
        int bestCap = INT_MAX;       // smallest fitting capacity seen so far

        for (int i = 0; i < (int)capacity.size(); ++i) {
            // Consider only boxes that can hold the item, and keep the smallest
            // such capacity. Strict "<" leaves bestIdx on the earliest tie.
            if (capacity[i] >= itemSize && capacity[i] < bestCap) {
                bestCap = capacity[i];
                bestIdx = i;
            }
        }

        return bestIdx;
    }
};
