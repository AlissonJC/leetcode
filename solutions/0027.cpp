/*
 * LeetCode 27 - Remove Element
 *
 * Remove every occurrence of val from nums in place and return k, the count of
 * remaining elements. The first k entries of nums must hold those remaining
 * values (in any order); anything past index k is ignored.
 *
 * Input  : vector<int>& nums (modified in place), int val.
 * Output : int k = number of elements not equal to val.
 * Constraints: 0 <= nums.length <= 100, 0 <= nums[i] <= 50, 0 <= val <= 100.
 *
 * Approach: two pointers. k is both the count of kept elements and the next
 *   write position. Scan once; whenever the current element differs from val,
 *   copy it to nums[k] and advance k. Elements equal to val are simply skipped,
 *   so the first k slots end up holding exactly the values to keep.
 *
 * Complexity: O(n) time, O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;                                   // count of kept elements / write index
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (nums[i] != val) {                    // keep everything that isn't val
                nums[k] = nums[i];
                ++k;
            }
        }
        return k;
    }
};
