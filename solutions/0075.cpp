/*
 * LeetCode 75 - Sort Colors
 *
 * An array nums holds n objects colored red, white, or blue, encoded as 0, 1, and 2.
 * Sort the array in place so all reds come first, then whites, then blues — i.e. sort
 * an array whose only values are 0, 1, 2 — without calling the library sort.
 *
 * Input  : vector<int>& nums (sorted in place). Output : none.
 *
 * Constraints: 1 <= n <= 300; every nums[i] is 0, 1, or 2.
 *   Follow-up: a single pass using O(1) extra space.
 *
 * Approach: Dutch National Flag three-way partition. Keep three pointers that carve the
 *   array into four regions with the invariant:
 *       [0, low)   are 0s,
 *       [low, mid) are 1s,
 *       [mid, high] are not yet examined,
 *       (high, n-1] are 2s.
 *   Scan with mid. On a 0, swap it down to the low boundary and advance both low and
 *   mid — the element swapped back is necessarily a 1 (it came from [low, mid)), so it
 *   needs no re-examination. On a 1, it is already in place; just advance mid. On a 2,
 *   swap it up to the high boundary and shrink high, but do NOT advance mid, because
 *   the value swapped in from the top is still unexamined. Stop once mid passes high.
 *
 * Complexity: O(n) time in a single pass, O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = (int)nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);   // send the 0 to the red region
                ++low; ++mid;                 // value returned to mid is a known 1
            } else if (nums[mid] == 1) {
                ++mid;                         // 1 already sits in the white region
            } else {                           // nums[mid] == 2
                swap(nums[mid], nums[high]);  // send the 2 to the blue region
                --high;                        // do not advance mid: swapped-in value unseen
            }
        }
    }
};
