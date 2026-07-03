/*
 * LeetCode 42 - Trapping Rain Water
 *
 * Given n non-negative integers where height[i] is the height of a unit-width
 * bar in an elevation map, compute how many units of water are trapped between
 * the bars after it rains. Water sits above bar i up to the lower of the
 * tallest bar to its left and the tallest bar to its right.
 *
 * Input  : vector<int> height - the bar heights left to right.
 * Output : int - total units of trapped water.
 *
 * Constraints: n == height.length; 1 <= n <= 2*10^4; 0 <= height[i] <= 10^5.
 *   (The maximum possible answer is about n * max(height) ~ 2*10^9, which still
 *   fits in a 32-bit int, but the running total is kept in long long so no
 *   intermediate addition can flirt with overflow.)
 *
 * Approach: the water resting on top of bar i equals
 *       min(maxLeft[i], maxRight[i]) - height[i]   (when positive),
 *   where maxLeft/maxRight are the tallest bars on each side. Instead of
 *   precomputing both arrays, sweep two pointers inward from the ends while
 *   tracking leftMax and rightMax seen so far. Always advance the pointer at
 *   the SHORTER wall: if height[left] < height[right], then the true tallest
 *   bar on the right is at least height[right], which already exceeds
 *   height[left] - so the left side is the binding constraint and leftMax alone
 *   fixes the water level at `left`. Symmetrically for the right. Each bar is
 *   thus resolved from the side that actually limits it, in a single pass.
 *
 * Complexity: O(n) time - each pointer moves inward at most n times total;
 *   O(1) extra space - only a handful of scalars, no auxiliary arrays.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int leftMax = 0, rightMax = 0;   // tallest bar seen from each end so far
        long long water = 0;             // wide accumulator, purely defensive

        // Converge the two pointers. The shorter of the two current walls is
        // always the one whose side is fully determined, so process it and step
        // inward.
        while (left < right) {
            if (height[left] < height[right]) {
                // Right side holds a wall (height[right]) taller than the left
                // pointer, so leftMax is the true ceiling for column `left`.
                if (height[left] >= leftMax) leftMax = height[left]; // new left wall, no water
                else water += leftMax - height[left];                // trapped above this bar
                ++left;
            } else {
                // Symmetric case: the left pointer is at least as tall, so
                // rightMax is the ceiling for column `right`.
                if (height[right] >= rightMax) rightMax = height[right];
                else water += rightMax - height[right];
                --right;
            }
        }

        return (int)water;
    }
};
