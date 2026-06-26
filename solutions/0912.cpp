/*
 * LeetCode 912 - Sort an Array
 *
 * Sort an integer array into ascending order and return it, WITHOUT calling any
 * built-in sort, in O(n log n) time and with the smallest possible extra space.
 * Values may repeat and may be negative.
 *
 * Input  : vector<int>& nums. Output : the same elements in ascending order.
 *
 * Constraints: 1 <= n <= 5*10^4; -5*10^4 <= nums[i] <= 5*10^4. Values fit in int;
 *   duplicates and negatives are allowed.
 *
 * Approach: heapsort, chosen because it sorts in place (O(1) auxiliary space) and
 *   guarantees O(n log n) even on adversarial inputs — unlike a naive quicksort,
 *   which degrades to O(n^2) on sorted or duplicate-heavy data. First arrange the
 *   array into a binary MAX-heap (the largest element ends up at index 0) by
 *   sifting down every internal node from the bottom up. Then repeatedly move the
 *   current maximum (the root) to the end of the unsorted prefix and sift the new
 *   root back down over the shrunken heap; each extraction places one element in
 *   its final ascending position, growing a sorted suffix.
 *
 * Complexity: O(n log n) time (n extractions, each an O(log n) sift-down) plus
 *   O(n) to build the heap; O(1) extra space (the sift-down loop is iterative).
 */

#include <vector>
#include <utility>
using namespace std;

class Solution {
    // Restore the max-heap property at subtree rooted at `root`, treating
    // indices [0, n) as the heap. Iterative, so it uses no recursion stack.
    void siftDown(vector<int>& a, int root, int n) {
        while (true) {
            int child = 2 * root + 1;               // left child
            if (child >= n)
                break;                              // root is a leaf: done
            // Pick the larger of the two children to compare against the root.
            if (child + 1 < n && a[child + 1] > a[child])
                ++child;
            if (a[root] >= a[child])
                break;                              // heap property already holds
            swap(a[root], a[child]);                // pull the larger child up
            root = child;                           // continue sinking from there
        }
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        int n = (int)nums.size();

        // Build a max-heap bottom-up: every node from the last internal one down
        // to the root gets sifted into place. This is O(n), not O(n log n).
        for (int i = n / 2 - 1; i >= 0; --i)
            siftDown(nums, i, n);

        // Repeatedly extract the maximum to the back. After moving the root to
        // index `end`, [end, n) is sorted; sift the new root over the prefix [0, end).
        for (int end = n - 1; end > 0; --end) {
            swap(nums[0], nums[end]);
            siftDown(nums, 0, end);
        }

        return nums;
    }
};
