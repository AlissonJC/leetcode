/*
 * LeetCode 215 - Kth Largest Element in an Array
 *
 * Given an integer array nums and an integer k, return the k-th largest element in
 * sorted order (not the k-th distinct value). Duplicates count, so for example the
 * 2nd largest of [3,3,2] is 3.
 *
 * Input  : vector<int> nums; int k. Output : int — the k-th largest element.
 *
 * Constraints: 1 <= k <= nums.length <= 1e5; -1e4 <= nums[i] <= 1e4. Values fit in a
 *   32-bit int and there is no accumulation, so no wider type is needed.
 *
 * Approach: the k-th largest element is exactly the element that would sit at index
 *   n - k once the array is sorted ascending, so find that order statistic with
 *   quickselect instead of sorting the whole array. Each step picks a random pivot and
 *   partitions the active range three ways (< pivot, == pivot, > pivot); the target
 *   index either lands in the equal block (answer found) or in the smaller/greater side
 *   to recurse into. Three-way partitioning keeps the work linear even on arrays full of
 *   equal values (a naive two-way partition degrades to O(n^2) there), and the random
 *   pivot defeats adversarial inputs crafted to slow a fixed pivot.
 *
 * Complexity: O(n) expected time (the searched range shrinks by a constant factor on
 *   average), O(n^2) only in a vanishingly unlikely worst case; O(1) extra space.
 */

#include <vector>
#include <random>
#include <chrono>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = (int)nums.size();
        int target = n - k;            // 0-based index of the answer in ascending order

        mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
        int l = 0, r = n - 1;
        while (true) {
            if (l == r) return nums[l];

            // Random pivot value from the current range.
            int pivot = nums[l + (int)(rng() % (unsigned)(r - l + 1))];

            // Dutch-flag partition: [l, lt) < pivot, [lt, gt] == pivot, (gt, r] > pivot.
            int lt = l, i = l, gt = r;
            while (i <= gt) {
                if (nums[i] < pivot)      swap(nums[i++], nums[lt++]);
                else if (nums[i] > pivot) swap(nums[i], nums[gt--]);
                else                      ++i;          // equal: leave it in the middle
            }

            // Narrow to the block that contains the target index.
            if (target < lt)      r = lt - 1;           // answer is among the smaller part
            else if (target > gt) l = gt + 1;           // answer is among the greater part
            else                  return pivot;         // target sits in the equal block
        }
    }
};
