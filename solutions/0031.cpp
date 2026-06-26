/*
 * LeetCode 31 - Next Permutation
 *
 * Rearrange nums into the next lexicographically greater permutation of its
 * numbers. If no greater permutation exists (the array is in descending order,
 * i.e. it is already the largest arrangement), wrap around to the smallest
 * permutation, which is the array sorted in ascending order. The change must be
 * done in place using only constant extra memory.
 *
 * Input  : vector<int>& nums, modified in place. Output : void.
 *
 * Constraints: 1 <= nums.length <= 100; 0 <= nums[i] <= 100. Tiny bounds, so the
 *   linear scan below is far inside any time limit and no wide integer type is
 *   needed.
 *
 * Approach (standard next-permutation, the algorithm behind std::next_permutation):
 *   A permutation grows to the next one by making the smallest possible increase
 *   at the rightmost position that can still grow.
 *     1. Scan from the right and find the first "pivot" index i where
 *        nums[i] < nums[i + 1]. Everything to the right of i is a non-increasing
 *        (descending) run — already the largest order for that suffix, so it
 *        cannot be advanced on its own.
 *     2. If no such pivot exists, the whole array is descending: it is the last
 *        permutation, so reverse it to get the first (ascending) one and return.
 *     3. Otherwise, in that descending suffix find the rightmost element nums[j]
 *        that is strictly greater than nums[i] — the smallest value still bigger
 *        than the pivot — and swap nums[i] with nums[j]. This is the minimal
 *        increase at position i.
 *     4. The suffix after i is still descending; reverse it to make it ascending,
 *        which is the smallest tail and completes the smallest larger permutation.
 *
 * Complexity: O(n) time (each step is a single pass over the array); O(1) extra
 *   space (all work is in-place swaps and a reverse).
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = (int)nums.size();

        // Step 1: find the pivot — the rightmost i with nums[i] < nums[i + 1].
        // The suffix to its right is non-increasing.
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1])
            --i;

        // Step 2/3: if a pivot exists, swap it with the smallest suffix element
        // that still exceeds it. (When i < 0 the array is fully descending and we
        // skip straight to the reverse, which yields the ascending permutation.)
        if (i >= 0) {
            // Scan the descending suffix from the right for the first value
            // greater than the pivot; being the rightmost such, it is the
            // smallest one larger than nums[i].
            int j = n - 1;
            while (nums[j] <= nums[i])
                --j;
            swap(nums[i], nums[j]);
        }

        // Step 4: the suffix after the pivot is descending; reversing it makes it
        // ascending (the smallest possible tail). When there was no pivot this
        // reverses the entire array into ascending order — the wrap-around case.
        reverse(nums.begin() + (i + 1), nums.end());
    }
};
