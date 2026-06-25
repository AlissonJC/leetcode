/*
 * LeetCode 11 - Container With Most Water
 *
 * The array height holds the heights of n vertical lines, where line i runs
 * between (i, 0) and (i, height[i]). Choose two lines so that, together with the
 * x-axis, they form a container holding the most water, and return that maximum
 * amount. Water held by lines i < j equals min(height[i], height[j]) * (j - i):
 * the shorter wall caps the depth and (j - i) is the width.
 *
 * Input  : vector<int> height. Output : int — the maximum container area.
 *
 * Constraints: 2 <= n <= 1e5; 0 <= height[i] <= 1e4. The largest possible area
 *   is 1e4 * (1e5 - 1) < 1e9, which fits in a 32-bit int, so no wider type is
 *   needed.
 *
 * Approach: two pointers starting at both ends. For the current pair the width
 *   is already the largest it can be, and the area is limited by the shorter of
 *   the two walls. Moving the taller wall inward only shrinks the width without
 *   ever lifting that limit, so it cannot beat the current area — only advancing
 *   the shorter wall has a chance to find a taller bound. Therefore discard the
 *   shorter wall each step (move its pointer inward) and keep the best area seen.
 *   The brute-force O(n^2) is too slow for n up to 1e5; this is O(n).
 *
 * Complexity: O(n) time (each pointer moves inward at most n times); O(1) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = (int)height.size() - 1;
        int best = 0;

        while (l < r) {
            int shorter = min(height[l], height[r]);
            best = max(best, shorter * (r - l));   // current width * limiting height

            // Advance the pointer at the shorter wall; the taller wall can never
            // yield a larger area with any smaller width.
            if (height[l] < height[r])
                ++l;
            else
                --r;
        }

        return best;
    }
};
