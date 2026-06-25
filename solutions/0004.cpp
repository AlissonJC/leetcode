/*
 * LeetCode 4 - Median of Two Sorted Arrays
 *
 * Given two sorted arrays nums1 (size m) and nums2 (size n), return the median
 * of the combined set in O(log(m + n)) time.
 *
 * Input  : sorted vector<int> nums1, nums2 (either may be empty).
 * Output : the median as a double.
 * Constraints: 0 <= m, n <= 1000, 1 <= m + n <= 2000, -1e6 <= values <= 1e6.
 *
 * Approach: binary-search the split point on the smaller array. Put i elements
 *   of nums1 and j = half - i elements of nums2 into the combined left half,
 *   where half = (m + n + 1) / 2. The split is correct when every left element
 *   is <= every right element, i.e. left1 <= right2 and left2 <= right1 (using
 *   +/-infinity sentinels at the ends). Then the median is the max of the left
 *   maxima (odd total) or the average of that and the min of the right minima
 *   (even total). If left1 > right2 take fewer from nums1, else take more.
 *   Searching the smaller side gives O(log(min(m, n))) <= O(log(m + n)).
 *
 * Complexity: O(log(min(m, n))) time, O(1) space.
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int m = (int)nums1.size(), n = (int)nums2.size();
        int half = (m + n + 1) / 2;                  // # elements in the combined left half
        int lo = 0, hi = m;
        while (lo <= hi) {
            int i = (lo + hi) / 2;                   // take i from nums1...
            int j = half - i;                        // ...and j from nums2 on the left
            int left1  = (i == 0) ? INT_MIN : nums1[i - 1];
            int right1 = (i == m) ? INT_MAX : nums1[i];
            int left2  = (j == 0) ? INT_MIN : nums2[j - 1];
            int right2 = (j == n) ? INT_MAX : nums2[j];
            if (left1 <= right2 && left2 <= right1) {            // valid split
                int maxLeft = max(left1, left2);
                if ((m + n) % 2 == 1) return maxLeft;            // odd total
                int minRight = min(right1, right2);
                return (maxLeft + minRight) / 2.0;              // even total
            } else if (left1 > right2) {
                hi = i - 1;                          // took too many from nums1
            } else {
                lo = i + 1;                          // took too few from nums1
            }
        }
        return 0.0;                                  // unreachable for valid input
    }
};
