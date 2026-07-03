/*
 * LeetCode 55 - Jump Game
 *
 * Starting at index 0 of the array nums, each nums[i] is the maximum forward
 * jump length from position i. Determine whether it is possible to reach the
 * last index.
 *
 * Input  : vector<int> nums - each entry is the maximum jump length from that
 *          position.
 * Output : bool - true if the last index is reachable from index 0.
 *
 * Constraints: 1 <= n == nums.length <= 10^4; 0 <= nums[i] <= 10^5.
 *
 * Approach: a single greedy left-to-right scan tracking `reach`, the farthest
 *   index reachable using every position visited so far. A position i is
 *   reachable exactly when i <= reach; the moment the scan meets an index that
 *   lies strictly beyond `reach`, no earlier (reachable) position could jump
 *   onto or past it, so the goal is unreachable and the answer is false.
 *   Otherwise stretch the frontier to max(reach, i + nums[i]); as soon as it
 *   covers the last index we can stop with true. Only the running maximum reach
 *   matters - not any specific path - which is why one pass suffices.
 *
 * Complexity: O(n) time - one scan; O(1) extra space - a single frontier index.
 *   No overflow: i + nums[i] <= 10^4 + 10^5 fits easily in int.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size();
        int reach = 0;   // farthest index reachable so far

        for (int i = 0; i < n; ++i) {
            // If index i sits beyond every jump seen so far, it is unreachable,
            // and so is everything after it.
            if (i > reach) return false;

            // Extend the frontier with the jump available from position i.
            reach = max(reach, i + nums[i]);

            // Frontier already covers the goal -> no need to scan further.
            if (reach >= n - 1) return true;
        }

        // Reached here only for n == 1 (start is already the last index).
        return true;
    }
};
