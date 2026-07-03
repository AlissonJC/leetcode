/*
 * LeetCode 45 - Jump Game II
 *
 * Starting at index 0 of the array nums, from index i you may jump forward to
 * any index in the range [i + 1, i + nums[i]]. Return the minimum number of
 * jumps needed to reach the last index. The test data guarantees that the last
 * index is always reachable.
 *
 * Input  : vector<int> nums - each entry is the maximum forward jump length
 *          from that position.
 * Output : int - the fewest jumps required to arrive at index n - 1.
 *
 * Constraints: 1 <= n == nums.length <= 10^4; 0 <= nums[i] <= 1000; the last
 *   index is guaranteed reachable.
 *
 * Approach: greedy breadth-first expansion done in a single left-to-right pass.
 *   Think of the indices reachable in exactly j jumps as "level j" of a BFS.
 *   Two frontiers track this without an explicit queue: curEnd is the last
 *   index of the current level (the farthest we can be after `jumps` jumps),
 *   and farthest is the best index any position in the current level can reach
 *   with one more jump. Sweep i from 0; keep farthest = max(farthest, i +
 *   nums[i]). The moment i reaches curEnd we have exhausted the current level,
 *   so one more jump is unavoidable: increment jumps and advance the boundary
 *   to farthest (the extent of the next level). Stop before the last index -
 *   arriving there ends the journey, and jumping FROM it is never needed. The
 *   number of boundary crossings is exactly the minimum jump count, since each
 *   crossing greedily reaches as far as any sequence of that many jumps could.
 *
 * Complexity: O(n) time - a single pass, each index visited once; O(1) space -
 *   only three scalar counters.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size();

        int jumps = 0;      // jumps taken so far
        int curEnd = 0;     // last index reachable with the current jump count
        int farthest = 0;   // farthest index reachable by taking one more jump

        // Stop at n - 2: once standing anywhere within reach of the last index,
        // the final boundary crossing already counted that arriving jump, so we
        // never need to process (or jump from) index n - 1 itself.
        for (int i = 0; i < n - 1; ++i) {
            // Extend the reach of the *next* level using position i.
            farthest = max(farthest, i + nums[i]);

            // Reached the edge of the current level -> a jump is forced, and the
            // next level stretches out to `farthest`.
            if (i == curEnd) {
                ++jumps;
                curEnd = farthest;
            }
        }

        // n == 1 falls straight through the loop with jumps == 0, which is
        // correct: we already start on the last index.
        return jumps;
    }
};
