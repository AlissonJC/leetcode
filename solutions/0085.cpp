/*
 * LeetCode 85 - Maximal Rectangle
 *
 * Given a rows x cols binary matrix of '0'/'1' characters, return the area of the largest
 * rectangle that contains only '1's.
 *
 * Input  : vector<vector<char>> matrix, each entry '0' or '1'.
 * Output : int — the maximum all-ones rectangle area.
 *
 * Constraints: 1 <= rows, cols <= 200, matrix[i][j] in {'0','1'}.
 *
 * Approach: Reduce each row to a histogram and reuse the "largest rectangle in a histogram"
 *   routine. Sweep rows top to bottom maintaining heights[j] = the number of consecutive
 *   '1's ending at the current row in column j (heights[j]+1 on a '1', reset to 0 on a '0').
 *   Any all-ones rectangle whose bottom edge sits on the current row corresponds exactly to
 *   a rectangle under this histogram, so the best such rectangle is the largest histogram
 *   rectangle for that row. Take the maximum of these over every row. The histogram query
 *   uses a monotonic stack of indices with increasing heights: when a shorter bar appears,
 *   pop taller bars and settle each one's widest rectangle (bounded by the first shorter bar
 *   on each side), with a virtual 0-height bar at the end to flush the stack.
 *
 * Overflow: area <= rows * cols = 200 * 200 = 40000, comfortably within int.
 *
 * Complexity: O(rows * cols) time (each column is pushed/popped once per row), O(cols) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = (int)matrix.size();
        if (rows == 0) return 0;
        int cols = (int)matrix[0].size();

        vector<int> heights(cols, 0);       // per-column run of consecutive '1's up to this row
        int best = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;  // extend or break the run
            best = max(best, largestInHistogram(heights));
        }
        return best;
    }

private:
    // Largest rectangle under a histogram, via a monotonic increasing-height index stack.
    int largestInHistogram(const vector<int>& h) {
        int n = (int)h.size();
        vector<int> st;                     // indices with strictly increasing heights
        st.reserve(n + 1);
        int best = 0;
        for (int i = 0; i <= n; ++i) {
            int cur = (i == n) ? 0 : h[i];  // trailing 0 forces every remaining bar to settle
            while (!st.empty() && h[st.back()] > cur) {
                int height = h[st.back()];
                st.pop_back();
                int left = st.empty() ? -1 : st.back();   // first shorter bar to the left
                int width = i - left - 1;                 // span between the two shorter bounds
                best = max(best, height * width);
            }
            st.push_back(i);
        }
        return best;
    }
};
