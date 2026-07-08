/*
 * LeetCode 2149 - Rearrange Array Elements by Sign
 *
 * Given a 0-indexed integer array nums of even length with an equal number of positive and
 * negative integers (no zeros), rearrange it so that every consecutive pair has opposite
 * signs, same-sign elements keep their original relative order, and the result starts with a
 * positive integer. Return the rearranged array.
 *
 * Input  : vector<int> nums (even length, equal positive/negative counts, all nonzero).
 * Output : vector<int> — the sign-interleaved arrangement starting with a positive.
 *
 * Constraints: 2 <= n <= 2e5, 1 <= |nums[i]| <= 1e5, equal number of positives and negatives.
 *
 * Approach: Place values by sign into fixed target slots of a fresh array. Positives fill the
 *   even indices 0, 2, 4, ... and negatives fill the odd indices 1, 3, 5, ..., each in the
 *   order encountered. One scan with two striding write pointers does it: the interleaving of
 *   even/odd slots guarantees consecutive opposite signs and a positive first element, while
 *   writing in traversal order preserves each sign group's relative order. Equal counts and no
 *   zeros mean the two pointer sequences land exactly on all n slots.
 *
 * Complexity: O(n) time, O(n) space for the output.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> res(n);
        int pos = 0, neg = 1;                 // next even slot for positives, next odd for negatives

        for (int v : nums) {
            if (v > 0) { res[pos] = v; pos += 2; }   // positives -> even indices, in order
            else       { res[neg] = v; neg += 2; }   // negatives -> odd indices, in order
        }
        return res;
    }
};
