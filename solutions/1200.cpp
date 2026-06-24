/*
 * LeetCode 1200 - Minimum Absolute Difference
 *
 * Given an array of distinct integers, find every pair of elements whose
 * absolute difference equals the minimum absolute difference over all pairs.
 * Return the pairs as [a, b] with a < b, listed in ascending order.
 *
 * Input  : vector<int> arr (distinct integers).
 * Output : vector<vector<int>> of the minimum-difference pairs, ascending.
 * Constraints: 2 <= arr.length <= 1e5, -1e6 <= arr[i] <= 1e6.
 *
 * Approach: after sorting, the smallest absolute difference must occur between
 *   two adjacent elements (any non-adjacent pair spans at least one adjacent gap,
 *   so its difference is no smaller). First scan the adjacent gaps to find the
 *   minimum, then scan again to emit every adjacent pair achieving it. Sorted
 *   order makes each pair already a < b and the whole list ascending.
 *
 * Complexity: O(n log n) time (the sort dominates), O(1) extra space.
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = (int)arr.size();

        // Minimum gap is among adjacent elements of the sorted array.
        int best = INT_MAX;
        for (int i = 1; i < n; ++i) best = min(best, arr[i] - arr[i - 1]);

        // Collect every adjacent pair whose gap equals that minimum.
        vector<vector<int>> result;
        for (int i = 1; i < n; ++i)
            if (arr[i] - arr[i - 1] == best)
                result.push_back({arr[i - 1], arr[i]});   // already a < b, ascending
        return result;
    }
};
