/*
 * LeetCode 1122 - Relative Sort Array
 *
 * Reorder arr1 so its elements follow the relative order given by arr2: every value that
 * appears in arr2 comes first, grouped and in arr2's order, and any value of arr1 not
 * present in arr2 is appended afterward in ascending order. arr2 has distinct values, and
 * every element of arr2 also occurs in arr1.
 *
 * Input  : vector<int> arr1, vector<int> arr2.
 * Output : the reordered arr1.
 *
 * Constraints: 1 <= arr1.length, arr2.length <= 1000; 0 <= arr1[i], arr2[i] <= 1000;
 *   arr2's elements are distinct and each occurs in arr1.
 *
 * Approach: counting sort keyed by value, since all values lie in the small fixed range
 *   [0, 1000]. Tally how many times each value occurs in arr1. Then emit results in two
 *   passes: first walk arr2 and, for each value x, output it count[x] times and clear its
 *   count (its multiplicity comes straight from arr1, its position from arr2). Second, walk
 *   values 0..1000 and output whatever counts remain — these are exactly the arr1 values
 *   missing from arr2, and scanning ascending places them in sorted order automatically.
 *   No comparison sort is needed for either part.
 *
 * Complexity: O(n + m + V) time (n = |arr1|, m = |arr2|, V = 1001 value range), O(V)
 *   space for the counts plus the O(n) output.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        const int MAXV = 1000;
        vector<int> count(MAXV + 1, 0);   // count[v] = occurrences of value v in arr1
        for (int x : arr1)
            count[x]++;

        vector<int> result;
        result.reserve(arr1.size());

        // Pass 1: values present in arr2, in arr2's order, each by its arr1 multiplicity.
        for (int x : arr2) {
            while (count[x] > 0) {
                result.push_back(x);
                --count[x];               // consume so pass 2 will not re-emit it
            }
        }

        // Pass 2: leftover values (not in arr2) in ascending order — scanning 0..MAXV
        // yields them already sorted.
        for (int v = 0; v <= MAXV; ++v) {
            while (count[v] > 0) {
                result.push_back(v);
                --count[v];
            }
        }

        return result;
    }
};
