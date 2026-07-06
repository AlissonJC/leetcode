/*
 * LeetCode 1365 - How Many Numbers Are Smaller Than the Current Number
 *
 * For each element nums[i], count how many other elements are strictly smaller than it,
 * and return those counts as an array aligned with nums (answer[i] corresponds to nums[i]).
 *
 * Input  : vector<int> nums.
 * Output : vector<int> answer, where answer[i] = #{ j : nums[j] < nums[i] }.
 *
 * Constraints: 2 <= nums.length <= 500; 0 <= nums[i] <= 100.
 *
 * Approach: counting sort with a prefix sum, since values live in the tiny range [0, 100].
 *   First tally count[v] = how many elements equal v. Then a prefix sum turns that into
 *   less[v] = count[0] + ... + count[v-1] = how many elements are strictly smaller than v.
 *   Because every element sharing a value has the same set of smaller elements, the answer
 *   for any nums[i] is simply less[nums[i]] — one lookup, no per-element scanning and no
 *   O(n log n) sort. Duplicates are handled for free: "strictly smaller" excludes equal
 *   values because the prefix stops at v-1.
 *
 * Complexity: O(n + V) time (V = 101 possible values), O(V) extra space plus the O(n)
 *   output.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        const int MAXV = 100;
        int count[MAXV + 1] = {0};              // count[v] = number of elements equal to v
        for (int x : nums)
            count[x]++;

        // less[v] = number of elements strictly less than v (prefix sum of counts).
        int less[MAXV + 1] = {0};
        for (int v = 1; v <= MAXV; ++v)
            less[v] = less[v - 1] + count[v - 1];

        // Each element's answer is just how many values fall below it.
        vector<int> answer;
        answer.reserve(nums.size());
        for (int x : nums)
            answer.push_back(less[x]);

        return answer;
    }
};
