/*
 * LeetCode 561 - Array Partition
 *
 * Given 2n integers, split them into n pairs so that the sum of the smaller element of
 * each pair is as large as possible; return that maximum sum.
 *
 * Input  : vector<int> nums of even length 2n.
 * Output : the maximized sum of pair minimums.
 *
 * Constraints: 1 <= n <= 1e4; nums.length == 2n; -1e4 <= nums[i] <= 1e4.
 *
 * Greedy: sort ascending and pair neighbours (nums[0],nums[1]), (nums[2],nums[3]), ...
 *   The min of each such pair is the element at the even index, so the answer is the sum
 *   of the elements sitting at indices 0,2,4,... of the sorted array. Why optimal: in any
 *   pairing the overall largest value is never counted (it is some pair's max), so we want
 *   its partner to be the next-largest value, "wasting" as little as possible; repeating
 *   this argument leaves consecutive sorted pairs. Each even-indexed element then survives
 *   as a counted minimum.
 *
 * Approach: because values lie in the small fixed range [-1e4, 1e4], skip the O(n log n)
 *   comparison sort and use counting sort. Tally counts over the 20001 possible values
 *   (shifted by +1e4 to index from 0). Walking values from smallest to largest reproduces
 *   sorted order; track the parity of the current sorted position so that, for a value
 *   appearing c times over c consecutive positions, we add it once for each even position
 *   it covers (ceil(c/2) if the run starts on an even index, else floor(c/2)). The run's
 *   length only flips the running parity when c is odd.
 *
 * Complexity: O(n + V) time where V = 20001 is the value range, O(V) space for the
 *   counts — no comparison sort.
 */

#include <vector>
using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        const int OFFSET = 10000;        // shift [-1e4,1e4] into [0,20000]
        const int RANGE = 20001;         // number of distinct possible values
        vector<int> count(RANGE, 0);
        for (int x : nums)
            count[x + OFFSET]++;

        long long sum = 0;               // wide accumulator; |answer| can reach 1e8
        bool nextIsEven = true;          // parity of the next position in sorted order
        for (int v = 0; v < RANGE; ++v) {
            int c = count[v];
            if (c == 0) continue;
            // Of c consecutive sorted positions, how many land on an even index?
            int evensHere = nextIsEven ? (c + 1) / 2 : c / 2;
            sum += (long long)(v - OFFSET) * evensHere;
            // The position after this run changes parity only when c is odd.
            if (c & 1)
                nextIsEven = !nextIsEven;
        }
        return (int)sum;
    }
};
