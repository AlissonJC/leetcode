/*
 * LeetCode 70 - Climbing Stairs
 *
 * A staircase has n steps; each move climbs 1 or 2 steps. Return the number of
 * distinct ways to reach the top.
 *
 * Input  : int n.   Output: number of distinct climbing sequences.
 * Constraints: 1 <= n <= 45.
 *
 * Approach: to land on step i the last move came from step i-1 (a 1-step) or
 *   step i-2 (a 2-step), so ways(i) = ways(i-1) + ways(i-2) -- the Fibonacci
 *   recurrence with ways(0) = ways(1) = 1. Roll it forward keeping only the last
 *   two values. Since ways(45) = 1836311903 < 2^31, an int holds every result.
 *
 * Complexity: O(n) time, O(1) space.
 */

class Solution {
public:
    int climbStairs(int n) {
        int prev2 = 1, prev1 = 1;        // ways(0) and ways(1)
        for (int i = 2; i <= n; ++i) {
            int cur = prev1 + prev2;     // ways(i) = ways(i-1) + ways(i-2)
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;                    // ways(n)
    }
};
