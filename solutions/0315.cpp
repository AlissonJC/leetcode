/*
 * LeetCode 315 - Count of Smaller Numbers After Self
 *
 * For each position i, count how many elements to its right are strictly smaller than
 * nums[i], and return those counts aligned with nums.
 *
 * Input  : vector<int> nums.
 * Output : vector<int> counts, counts[i] = #{ j > i : nums[j] < nums[i] }.
 *
 * Constraints: 1 <= nums.length <= 1e5; -1e4 <= nums[i] <= 1e4.
 *
 * Approach: this is an "inversions, tallied per element" problem, solved with merge sort in
 *   O(n log n). Sort an array of original indices by their values. When merging two halves
 *   (left = original positions [lo, mid], right = [mid+1, hi], each already sorted by value
 *   ascending), every right-half element has a larger original position than every left-half
 *   element. So at the moment a left element idx[a] is emitted, the right elements already
 *   pulled ahead of it are exactly those that are strictly smaller AND lie to its right --
 *   add that running count to counts[idx[a]]. Breaking ties toward the left (<=) ensures only
 *   strictly-smaller right elements are counted. Summed over all merges, each element's total
 *   is its answer.
 *
 * Complexity: O(n log n) time, O(n) space for the index array, temp buffer, and counts.
 */

#include <vector>
using namespace std;

class Solution {
    vector<int> order;   // original indices, reordered by value as the sort progresses
    vector<int> buffer;  // scratch space for merging
    vector<int> counts;  // answer accumulator
    const vector<int>* nums = nullptr;

    void mergeSort(int lo, int hi) {
        if (lo >= hi)
            return;
        int mid = lo + (hi - lo) / 2;
        mergeSort(lo, mid);
        mergeSort(mid + 1, hi);

        // Merge order[lo..mid] and order[mid+1..hi], both ascending by value.
        int a = lo, b = mid + 1, t = lo;
        while (a <= mid && b <= hi) {
            if ((*nums)[order[a]] <= (*nums)[order[b]]) {
                // Right elements already emitted (b - (mid+1)) are strictly smaller and to
                // the right of order[a].
                counts[order[a]] += b - (mid + 1);
                buffer[t++] = order[a++];
            } else {
                buffer[t++] = order[b++];
            }
        }
        while (a <= mid) {
            counts[order[a]] += b - (mid + 1);   // every right element was smaller
            buffer[t++] = order[a++];
        }
        while (b <= hi)
            buffer[t++] = order[b++];

        for (int k = lo; k <= hi; ++k)
            order[k] = buffer[k];
    }

public:
    vector<int> countSmaller(vector<int>& numsRef) {
        int n = (int)numsRef.size();
        nums = &numsRef;
        counts.assign(n, 0);
        order.resize(n);
        buffer.resize(n);
        for (int i = 0; i < n; ++i)
            order[i] = i;
        mergeSort(0, n - 1);
        return counts;
    }
};
