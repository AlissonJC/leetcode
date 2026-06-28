/*
 * LeetCode 1846 - Maximum Element After Decreasing and Rearranging
 *
 * Given an array arr of positive integers, two operations may be applied any
 * number of times: decrease an element to a smaller positive integer, and
 * rearrange the elements into any order. The goal is to satisfy two conditions
 * simultaneously: arr[0] must equal 1, and every pair of adjacent elements must
 * differ by at most 1 (abs(arr[i] - arr[i-1]) <= 1). Return the largest value
 * that can still appear in arr once those conditions hold.
 *
 * Input  : vector<int> arr. Output : int — the maximum reachable element.
 *
 * Constraints: 1 <= arr.length <= 1e5; 1 <= arr[i] <= 1e9. Because the chain
 *   starts at 1 and grows by at most 1 per step, the answer never exceeds the
 *   length n (<= 1e5), so a 32-bit int is more than enough.
 *
 * Approach: only decreasing is allowed, never increasing, and order is free, so
 *   place the values in ascending order — that lets each element support the
 *   tallest possible staircase. Force the first element to 1. Then sweep left to
 *   right capping each element at one more than its predecessor: a value larger
 *   than prev+1 must be decreased to prev+1 to respect the adjacency rule, while
 *   a value already <= prev+1 stays as it is (we cannot raise it). Sorting first
 *   guarantees prev+1 is always an attainable target, so this builds the
 *   steepest valid chain and the last (largest) element is the answer.
 *
 * Complexity: O(n log n) time dominated by the sort; O(1) extra space (the
 *   array is reshaped in place).
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        // The first element is forced down to 1; the chain must start there.
        arr[0] = 1;

        // Each element can climb at most one step above its predecessor. If it
        // is already lower, leave it (we may only decrease, not increase).
        for (size_t i = 1; i < arr.size(); ++i)
            arr[i] = min(arr[i], arr[i - 1] + 1);

        // After the sweep the tallest reachable value sits at the end.
        return arr.back();
    }
};
