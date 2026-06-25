/*
 * LeetCode 3699 - Number of ZigZag Arrays I
 *
 * Count arrays of length n with values in [l, r] where no two adjacent elements
 * are equal and no three consecutive elements are strictly increasing or
 * strictly decreasing (a "zigzag" array). Return the count modulo 1e9+7.
 *
 * Input  : ints n, l, r.   Output: the count mod 1e9+7.
 * Constraints: 3 <= n <= 2000, 1 <= l < r <= 2000.
 *
 * Approach: the answer depends only on m = r - l + 1, the number of distinct
 *   values. Forbidding equal neighbours and any three-in-a-row monotone run
 *   forces the up/down comparison pattern to strictly alternate. Let up[v] be
 *   the number of length-i zigzags ending at value v whose last step is up; by
 *   reflection symmetry the "down" counts are the mirror image, so one length-m
 *   vector suffices and one step is new[v] = sum over w >= m+2-v of up[w] (a
 *   suffix sum, computed in O(m)). Start with all ones (length 1) and roll
 *   forward n-1 times; the answer is 2 * sum(up) at length n. With n, m <= 2000
 *   the plain O(n*m) DP (~4e6 steps) is fast, so no matrix exponentiation needed.
 *
 * Complexity: O(n * m) time, O(m) space.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const long long MOD = 1000000007LL;
        int m = r - l + 1;                          // only the value count matters
        vector<long long> up(m + 2, 0), suf(m + 2, 0), nu(m + 2, 0);
        for (int v = 1; v <= m; ++v) up[v] = 1;     // length 1: one array per value

        for (int i = 2; i <= n; ++i) {
            suf[m + 1] = 0;                          // suffix sums of the current layer
            for (int k = m; k >= 1; --k) suf[k] = (suf[k + 1] + up[k]) % MOD;
            for (int v = 1; v <= m; ++v) {
                int lo = m + 2 - v;                  // new[v] = sum of up[lo .. m]
                nu[v] = (lo <= m) ? suf[lo] : 0;     // lo > m (only v = 1) -> empty -> 0
            }
            swap(up, nu);
        }

        long long total = 0;
        for (int v = 1; v <= m; ++v) total = (total + up[v]) % MOD;
        return (int)(2 * total % MOD);              // "up" and mirror "down" halves
    }
};
