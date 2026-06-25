/*
 * LeetCode 88 - Merge Sorted Array
 *
 * Merge nums2 (n elements) into nums1 (m valid elements followed by n zero
 * placeholders) so nums1 holds all m + n values in non-decreasing order. The
 * result is stored in place in nums1; nothing is returned.
 *
 * Input  : vector<int> nums1 (length m+n), int m, vector<int> nums2, int n.
 * Output : none -- nums1 is modified in place.
 * Constraints: 0 <= m, n <= 200, 1 <= m + n <= 200, |values| <= 1e9.
 *
 * Approach: merge from the back. Place the larger of the two current tails into
 *   the last free slot and step that pointer left. Writing from the end means we
 *   only ever overwrite the trailing zero slots, never an nums1 element we still
 *   need. The loop runs until nums2 is exhausted; any nums1 elements left are
 *   already in their final positions.
 *
 * Complexity: O(m + n) time, O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;   // read tails of nums1/nums2, write at k
        while (j >= 0) {                            // still have nums2 elements to place
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];            // nums1's tail is larger
            } else {
                nums1[k--] = nums2[j--];            // take from nums2 (also when nums1 ran out)
            }
        }
    }
};
