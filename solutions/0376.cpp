/*
 * LeetCode 376 - Wiggle Subsequence
 *
 * A wiggle sequence has strictly alternating positive/negative differences between
 * successive elements (the first difference may be either sign; length-0/1 sequences and a
 * length-2 sequence of two unequal values are trivially wiggle). Given nums, return the
 * length of its longest wiggle SUBSEQUENCE (elements kept in order, some deleted).
 *
 * Input  : vector<int> nums.
 * Output : int — length of the longest wiggle subsequence.
 *
 * Constraints: 1 <= n <= 1000, 0 <= nums[i] <= 1000.
 *
 * Approach: Greedy in O(n). Keep two running lengths: 'up' = the longest wiggle subsequence
 *   built so far whose last step goes UP, and 'down' = the longest whose last step goes DOWN.
 *   Scanning left to right, a strict rise (nums[i] > nums[i-1]) can only extend a subsequence
 *   that last went down, so up = down + 1; symmetrically a strict fall gives down = up + 1;
 *   equal neighbors change nothing (a zero difference cannot be part of a wiggle). The answer
 *   is max(up, down). Intuitively the longest wiggle just walks between consecutive local
 *   extrema, so its length is one plus the number of direction changes.
 *
 * Complexity: O(n) time, O(1) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int up = 1, down = 1;               // a single element is a length-1 wiggle either way

        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1])
                up = down + 1;              // a rise extends the best "last step down" run
            else if (nums[i] < nums[i - 1])
                down = up + 1;              // a fall extends the best "last step up" run
            // equal neighbors: skip — a zero difference can't belong to a wiggle
        }
        return max(up, down);
    }
};
