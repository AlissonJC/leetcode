/*
 * LeetCode 1985 - Find the Kth Largest Integer in the Array
 *
 * Each string in nums is a non-negative integer written without leading zeros. Treating
 * the strings as the integers they represent (duplicates counted separately), return the
 * string that is the k-th largest (1-indexed).
 *
 * Input  : vector<string> nums; int k. Output : string — the k-th largest value.
 *
 * Constraints: 1 <= k <= nums.length <= 1e4; 1 <= nums[i].length <= 100; digits only,
 *   no leading zeros. Numbers reach 100 digits, far beyond any built-in integer type, so
 *   the values are compared directly on their string form.
 *
 * Approach: with no leading zeros, comparing two integer strings is easy — the one with
 *   more digits is larger, and when the lengths match a plain lexicographic comparison of
 *   the digit strings equals the numeric comparison. Using that order, a selection
 *   (nth_element) puts the k-th largest at index k-1 without sorting the whole array.
 *
 * Complexity: O(n * L) expected time, where n = nums.size() and L = max string length
 *   (each comparison costs O(L)); O(1) extra space.
 */

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {
        // Strict "numerically greater" order: more digits wins; ties broken lexically,
        // which is the same as numeric order for equal-length digit strings.
        auto greaterNum = [](const string& a, const string& b) {
            if (a.size() != b.size()) return a.size() > b.size();
            return a > b;
        };

        // Place the k-th largest at index k-1; everything before it is no smaller.
        nth_element(nums.begin(), nums.begin() + (k - 1), nums.end(), greaterNum);
        return nums[k - 1];
    }
};
