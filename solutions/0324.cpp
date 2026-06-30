/*
 * LeetCode 324 - Wiggle Sort II
 *
 * Reorder the array in place so that it strictly wiggles:
 * nums[0] < nums[1] > nums[2] < nums[3] > ... (odd indices are peaks, even indices are
 * valleys, all inequalities strict). The input is guaranteed to admit such an ordering.
 *
 * Input  : vector<int> nums (modified in place). Output : none.
 *
 * Constraints: 1 <= nums.length <= 5e4; 0 <= nums[i] <= 5000. Values fit in int and a
 *   valid arrangement always exists, so the construction below never fails.
 *
 * Approach: sort a copy, then split it into a smaller half and a larger half and deal
 *   them into the original array — even indices (the valleys) get the smaller half, odd
 *   indices (the peaks) get the larger half. The key detail is to fill each half from
 *   its HIGH end downward: that places the largest small-half value at index 0 and the
 *   smallest large-half value at the final odd index, pushing equal median values as far
 *   apart as possible so two equal numbers can never become neighbours. Reading the
 *   halves in ascending order instead would let duplicated medians collide in the middle.
 *
 * Complexity: O(n log n) time (dominated by the sort), O(n) extra space for the copy.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> s(nums);
        sort(s.begin(), s.end());

        // mid = last index of the smaller half. Even positions consume s[mid..0]
        // (high to low); odd positions consume s[n-1..mid+1] (high to low).
        int mid = (n - 1) / 2;
        int j = mid, k = n - 1;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) nums[i] = s[j--];   // valley: largest remaining small-half value
            else            nums[i] = s[k--];   // peak: largest remaining large-half value
        }
    }
};
