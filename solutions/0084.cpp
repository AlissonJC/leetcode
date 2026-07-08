/*
 * LeetCode 84 - Largest Rectangle in Histogram
 *
 * Given heights representing a histogram where every bar has width 1, return the area of
 * the largest axis-aligned rectangle that fits entirely under the bars.
 *
 * Input  : vector<int> heights.
 * Output : int — the maximum rectangle area.
 *
 * Constraints: 1 <= n <= 1e5, 0 <= heights[i] <= 1e4.
 *
 * Approach: For each bar, the tallest rectangle that uses it as the limiting (shortest)
 *   height extends left until a strictly shorter bar and right until a strictly shorter
 *   bar. Find those spans in one pass with a stack of indices kept in increasing height.
 *   When the current bar is shorter than the bar on top of the stack, that top bar can
 *   grow no further right, so pop it: its rectangle has height heights[top] and width
 *   spanning from just after the new stack top (its first-shorter bar on the left) up to
 *   just before the current index (its first-shorter bar on the right). Processing a
 *   virtual 0-height bar at index n flushes everything still on the stack.
 *
 * Overflow: area = height * width <= 1e4 * 1e5 = 1e9 fits in int, but the product is formed
 *   in 64-bit before the max to leave no doubt.
 *
 * Complexity: O(n) time (each index is pushed and popped once), O(n) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = (int)heights.size();
        vector<int> st;                       // indices with strictly increasing heights
        st.reserve(n + 1);
        long long best = 0;

        for (int i = 0; i <= n; ++i) {
            int h = (i == n) ? 0 : heights[i];         // sentinel 0 flushes the stack at the end
            // Any bar taller than the current one is now bounded on the right by i.
            while (!st.empty() && heights[st.back()] > h) {
                int height = heights[st.back()];
                st.pop_back();
                int leftBound = st.empty() ? -1 : st.back();   // first shorter bar to the left
                long long width = i - leftBound - 1;           // bars strictly between the bounds
                best = max(best, (long long)height * width);
            }
            st.push_back(i);
        }
        return (int)best;
    }
};
