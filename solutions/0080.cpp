/*
 * LeetCode 80 - Remove Duplicates from Sorted Array II
 *
 * Given an integer array nums sorted in non-decreasing order, remove duplicates
 * in place so that each unique value appears at most twice, preserving relative
 * order. The kept elements must occupy the first k slots of nums; return k. Only
 * O(1) extra memory is allowed — no second array.
 *
 * Input  : vector<int>& nums, sorted non-decreasing (modified in place).
 * Output : int k — the new length; nums[0..k-1] holds the deduplicated prefix.
 *          (Whatever remains beyond index k-1 is irrelevant, per the custom judge.)
 *
 * Constraints: 1 <= n <= 3e4, -1e4 <= nums[i] <= 1e4, nums sorted non-decreasing.
 *
 * Approach: A single write pointer k marks how many elements have been committed to
 *   the output prefix. Walk every value x left to right and decide whether to keep it:
 *     - If k < 2, we have not yet placed two elements at all, so always keep x.
 *     - Otherwise keep x only when x != nums[k-2]. Since the array is sorted, equal
 *       values are contiguous, so nums[k-2] == x would mean the last two committed
 *       slots already hold this same value — i.e. two copies are in — and this third+
 *       copy must be dropped. Any x != nums[k-2] is safe to append.
 *   This "compare against the element two positions back in the output" trick
 *   generalizes directly: for an at-most-M rule, compare against nums[k-M].
 *
 *   In-place safety: the write index k never runs ahead of the read index, so when we
 *   assign nums[k] = x we only ever overwrite the current slot or one already read and
 *   passed. Reading x (a copy) at the top of each iteration keeps that write harmless.
 *
 * Complexity: O(n) time (one pass), O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 0;                          // number of committed elements = next write slot
        for (int x : nums) {                // x is a copy of the current element
            // Keep the first two unconditionally; afterwards keep x only if the slot
            // two back differs, which (array being sorted) means < 2 copies are placed.
            if (k < 2 || nums[k - 2] != x)
                nums[k++] = x;
        }
        return k;                           // nums[0..k-1] is the answer prefix
    }
};
