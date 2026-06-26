/*
 * LeetCode 996 - Number of Squareful Arrays
 *
 * An array is "squareful" if the sum of every pair of ADJACENT elements is a
 * perfect square. Given nums, count how many of its permutations are squareful.
 * Two permutations are considered different if they differ at any index, but
 * permutations that are identical element-by-element (which happens when nums has
 * repeated values) are counted only once.
 *
 * Input  : vector<int>& nums. Output : int — number of distinct squareful perms.
 *
 * Constraints: 1 <= nums.length <= 12; 0 <= nums[i] <= 10^9. With n <= 12 the raw
 *   permutation count (12! ~ 4.8e8) fits in a 32-bit int, but we never enumerate
 *   them all: the perfect-square adjacency requirement prunes the search hard.
 *   A pairwise sum can reach 2*10^9, so sums are handled as long long.
 *
 * Approach: this is essentially counting Hamiltonian paths in the graph whose
 *   edges join indices i, j when nums[i] + nums[j] is a perfect square. Sort nums
 *   so equal values are adjacent, then backtrack: extend the current path with any
 *   unused index whose value forms a perfect-square sum with the last placed
 *   element. Two prunes keep it fast and correct:
 *     - perfect-square check: never place a neighbour that breaks the squareful
 *       property, so dead branches are abandoned immediately;
 *     - duplicate guard (as in Permutations II): when nums[i] == nums[i-1] and the
 *       equal predecessor i-1 is unused, skip i, forcing equal values into a fixed
 *       left-to-right order so identical permutations are generated only once.
 *   Each completed full-length path is one distinct squareful permutation.
 *
 * Complexity: O(n^2 * 2^n) in the worst conceivable case, but in practice the
 *   square constraint makes the explored tree tiny. O(n) extra space for the
 *   recursion stack and the used[] array.
 */

#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        // Sort so duplicates sit next to each other (needed by the dedup guard).
        sort(nums.begin(), nums.end());

        count = 0;
        vector<bool> used(nums.size(), false);
        // last = -1 marks "no element placed yet", so the first pick is unrestricted.
        backtrack(nums, used, /*placed=*/0, /*last=*/-1);
        return count;
    }

private:
    int count;

    // Returns true iff x is a non-negative perfect square. Uses sqrtl then nudges
    // the candidate root to defend against floating-point rounding near boundaries.
    static bool isPerfectSquare(long long x) {
        if (x < 0) return false;
        long long r = (long long)sqrtl((long double)x);
        while (r * r > x) --r;
        while ((r + 1) * (r + 1) <= x) ++r;
        return r * r == x;
    }

    // placed = how many elements are already in the path; last = the index of the
    // most recently placed element (-1 if none yet).
    void backtrack(const vector<int>& nums, vector<bool>& used, int placed, int last) {
        // A full-length path is one complete squareful permutation.
        if (placed == (int)nums.size()) {
            ++count;
            return;
        }

        for (int i = 0; i < (int)nums.size(); ++i) {
            if (used[i])
                continue;

            // Dedup: only the leftmost still-unused copy of a repeated value may be
            // chosen at this step, otherwise we'd recount the same permutation.
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
                continue;

            // Squareful prune: every adjacent pair must sum to a perfect square.
            // The first element (last == -1) has no left neighbour, so it is free.
            if (last != -1 &&
                !isPerfectSquare((long long)nums[last] + nums[i]))
                continue;

            used[i] = true;
            backtrack(nums, used, placed + 1, i);
            used[i] = false;        // undo the choice (backtracking)
        }
    }
};
