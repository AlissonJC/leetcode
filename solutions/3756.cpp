/*
 * LeetCode 3756 - Concatenate Non-Zero Digits and Multiply by Sum II
 *
 * Given a digit string s of length m and q range queries [l, r]. For each query,
 * take the substring s[l..r], drop every zero, and concatenate the surviving
 * non-zero digits in their original order into an integer x (x = 0 if the range has
 * no non-zero digit). Let sum be the sum of x's digits. The query answer is x * sum,
 * returned modulo 1e9 + 7.
 *
 * Input  : string s, vector<vector<int>> queries (each {l, r}, 0-indexed, l <= r).
 * Output : vector<int> answer — one value per query, each already reduced mod 1e9 + 7.
 *
 * Constraints: 1 <= m, q <= 1e5. Rescanning each range is O(m) per query, i.e. up to
 *   ~1e10 operations overall — far too slow. We need O(1) per query after O(m) prep.
 *
 * Approach: The number x of a range is the decimal number spelled out by the non-zero
 *   digits inside it, so concatenation obeys base-10 place value, except only the KEPT
 *   (non-zero) digits advance the place. Two prefix arrays capture this:
 *
 *     pre[i] = value (mod p) of concatenating the non-zero digits of s[0..i-1]
 *     nz[i]  = how many non-zero digits lie in s[0..i-1]
 *
 *   Splitting the prefix over [0..r] at position l gives
 *       pre[r+1] = pre[l] * 10^k + X            (mod p),
 *   where X is the range's concatenation we want and k = nz[r+1] - nz[l] is the count
 *   of non-zero digits actually placed inside [l..r]. Solving for X:
 *       X = pre[r+1] - pre[l] * 10^k            (mod p).
 *   The exponent is 10^k, NOT 10^(r-l+1): interior zeros are discarded and never shift
 *   the place value, so only kept digits count.
 *
 *   sum is simply the sum of the range's digits (zeros add nothing), which equals the
 *   digit sum of x — a plain prefix sum. It is at most 9 * 1e5 = 9e5 < p, so it needs
 *   no modular reduction of its own. The answer is (X * sum) mod p.
 *
 * Overflow / modular care: pre[l] and 10^k are each < p (~1e9), so their product is
 *   < 1e18 and fits in a signed 64-bit long long before the mod. The subtraction may go
 *   negative, so add p once before the final mod. sum < p keeps X * sum < 1e18 as well.
 *
 * Complexity: O(m + q) time, O(m) space.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1000000007;
        int m = (int)s.size();

        // pre[i]: concatenation of the non-zero digits of s[0..i-1], mod p.
        // nz[i] : number of non-zero digits in s[0..i-1].
        // ds[i] : exact sum of the digit values in s[0..i-1] (bounded by 9e5).
        vector<long long> pre(m + 1, 0);
        vector<int> nz(m + 1, 0), ds(m + 1, 0);

        // pw[k] = 10^k mod p. The largest exponent we ever need is the total non-zero
        // count, which is at most m, so precomputing up to m suffices.
        vector<long long> pw(m + 1, 1);
        for (int k = 1; k <= m; ++k) pw[k] = pw[k - 1] * 10 % MOD;

        for (int i = 0; i < m; ++i) {
            int d = s[i] - '0';
            if (d != 0) {                                // non-zero digit: place it
                pre[i + 1] = (pre[i] * 10 + d) % MOD;    //   x = x*10 + d, in base 10
                nz[i + 1]  = nz[i] + 1;
            } else {                                     // zero: carries no place value
                pre[i + 1] = pre[i];
                nz[i + 1]  = nz[i];
            }
            ds[i + 1] = ds[i] + d;                       // zeros add 0 to the digit sum
        }

        vector<int> answer;
        answer.reserve(queries.size());
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            int k = nz[r + 1] - nz[l];                   // non-zero digits placed in [l..r]
            // X = pre[r+1] - pre[l]*10^k (mod p); +MOD guards the possible negative.
            long long X = (pre[r + 1] - pre[l] * pw[k] % MOD + MOD) % MOD;
            long long sum = ds[r + 1] - ds[l];           // digit sum of range == digit sum of x
            answer.push_back((int)(X * (sum % MOD) % MOD));
        }
        return answer;
    }
};
