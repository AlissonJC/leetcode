/*
 * LeetCode 41 - First Missing Positive
 *
 * Given an unsorted integer array nums, return the smallest positive integer that
 * does not appear in it. The algorithm must run in O(n) time and use O(1) auxiliary
 * space (beyond the input array itself).
 *
 * Input  : vector<int>& nums (may contain negatives, zeros, duplicates, huge ints).
 * Output : int — the smallest absent positive integer.
 *
 * Constraints: 1 <= n <= 10^5; -2^31 <= nums[i] <= 2^31 - 1. Values can be the full
 *   32-bit range, so range checks must guard array indexing.
 *
 * Approach: index-as-hash (cyclic sort). With n elements, the answer is always in
 *   [1, n+1]: if every value 1..n is present the answer is n+1, otherwise some value
 *   in 1..n is missing. So only values in [1, n] matter, and the array itself can act
 *   as the hash table by storing value v at index v-1. Walk the array and, whenever
 *   nums[i] is a value in [1, n] that is not already sitting in its home slot, swap it
 *   there; the guard nums[nums[i]-1] != nums[i] both detects "already placed" and
 *   stops duplicates from looping forever. Each successful swap fixes one value
 *   permanently, so the total work is O(n). Afterwards the first index i whose slot
 *   does not hold i+1 reveals the missing positive; if all slots match, return n+1.
 *
 * Complexity: O(n) time (amortized — at most n placement swaps plus two linear
 *   scans) and O(1) extra space (rearranged in place).
 */

#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = (int)nums.size();

        // Place each in-range value v at its home index v-1. The third condition
        // skips values already home and prevents infinite swapping on duplicates.
        for (int i = 0; i < n; ++i) {
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // The first slot not holding its expected value i+1 is the missing positive.
        for (int i = 0; i < n; ++i)
            if (nums[i] != i + 1)
                return i + 1;

        // Slots 0..n-1 hold exactly 1..n, so the smallest missing positive is n+1.
        return n + 1;
    }
};
