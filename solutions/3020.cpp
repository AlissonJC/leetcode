/*
 * LeetCode 3020 - Find the Maximum Number of Elements in Subset
 *
 * Given an array of positive integers nums, choose a subset whose elements can
 * be arranged as the palindrome [x, x^2, x^4, ..., x^(k/2), x^k, x^(k/2), ...,
 * x^4, x^2, x], where k is a power of 2. Every level x^(2^i) below the peak is
 * used twice (once going up, once coming down) and the peak x^k once, so the
 * subset size is always odd. Return the largest such size.
 *
 * Input  : vector<int> nums (function argument, no stdin/stdout).
 * Output : int, the maximum subset size that forms the pattern.
 *
 * Constraints: 2 <= nums.length <= 1e5, 1 <= nums[i] <= 1e9.
 *
 * Approach: count occurrences of each value. For each base x != 1, walk the
 *   chain x, x^2, x^4, ... ; as long as the current level has at least two
 *   copies it can sit on both sides of the palindrome (add 2, then square).
 *   When the walk stops, the value it stopped on is the peak if it is present
 *   (used once -> +1); otherwise the last doubled level had no peak above it,
 *   so undo one side of it (-1). The base x == 1 is handled apart because
 *   1^(2^i) == 1 would loop forever; there the answer is simply the longest
 *   odd-length run of 1s. A single element is always a valid length-1 subset.
 *
 * Complexity: O(n) time (each chain squares, so it has O(log log max) steps),
 *   O(n) space for the frequency map.
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        // Use 64-bit keys: squaring a value up to 1e9 reaches 1e18, which must
        // still be looked up (and will simply be absent) without overflowing.
        unordered_map<long long, int> cnt;
        for (int v : nums) cnt[(long long)v]++;

        int ans = 1;  // any single element forms the length-1 pattern [x]

        // x == 1: every power equals 1, so pick the largest odd count of 1s.
        auto one = cnt.find(1);
        if (one != cnt.end()) {
            int c = one->second;
            ans = max(ans, (c % 2 == 1) ? c : c - 1);
        }

        for (const auto& [x, c] : cnt) {
            if (x == 1) continue;  // handled above; would loop since 1*1 == 1

            long long cur = x;
            int len = 0;
            // Extend while the level can occupy both palindrome sides (>= 2).
            // Read-only lookups only — never operator[] here, which would
            // insert keys and invalidate this very iteration.
            while (true) {
                auto it = cnt.find(cur);
                if (it == cnt.end() || it->second < 2) break;
                len += 2;
                cur = cur * cur;  // safe: once cur > 1e9 the next find misses
            }
            // cur is the first level we could not double. If it exists it is
            // the single peak (+1); otherwise drop one side of the last level.
            if (cnt.find(cur) != cnt.end()) len += 1;
            else len -= 1;

            ans = max(ans, len);
        }

        return ans;
    }
};
