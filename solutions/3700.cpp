/*
 * LeetCode 3700 - Number of ZigZag Arrays II
 *
 * Count arrays of length n whose elements lie in [l, r], where no two adjacent
 * elements are equal and no three consecutive elements are strictly increasing
 * or strictly decreasing (a "zigzag" array). Return the count modulo 1e9+7.
 *
 * Input  : ints n, l, r (function arguments). Output: the count mod 1e9+7.
 * Constraints: 3 <= n <= 1e9, 1 <= l < r <= 75.
 *
 * Approach: the conditions depend only on the relative order of values, so the
 *   answer depends only on m = r - l + 1, the number of distinct values (2..75).
 *   Forbidding equal neighbours and any three-in-a-row monotone run forces the
 *   up/down comparison pattern to alternate. Let up[v] count zigzag arrays
 *   ending at value v with the last step up; by reflection symmetry the "down"
 *   counts are the mirror image, so one length-m vector suffices and one step is
 *   the linear map  new[v] = sum_{w >= m-v} old[w]  (0-indexed). Encode that as
 *   an m x m 0/1 matrix M; after n-1 steps from the all-ones start the answer is
 *   2 * (sum of all entries of M^(n-1)). Since n is up to 1e9, raise M to the
 *   (n-1) power by fast matrix exponentiation.
 *
 * Complexity: O(m^3 log n) time, O(m^2) space (m <= 75).
 */

#include <vector>
using namespace std;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;                       // only the value count matters
        // Transition matrix: M[v][w] = 1 iff w >= m - v  (a suffix sum per row).
        vector<vector<long long>> M(m, vector<long long>(m, 0));
        for (int v = 0; v < m; ++v)
            for (int w = m - v; w < m; ++w)
                M[v][w] = 1;

        vector<vector<long long>> R = matpow(M, (long long)n - 1);

        // Total zigzag arrays = 2 * (sum of all entries of M^(n-1)).
        long long total = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                total = (total + R[i][j]) % MOD;
        return (int)(2 * total % MOD);
    }

private:
    static const long long MOD = 1000000007LL;

    vector<vector<long long>> matmul(const vector<vector<long long>>& A,
                                     const vector<vector<long long>>& B) {
        int m = (int)A.size();
        vector<vector<long long>> C(m, vector<long long>(m, 0));
        for (int i = 0; i < m; ++i)
            for (int k = 0; k < m; ++k) {
                if (!A[i][k]) continue;          // skip zeros (M starts sparse)
                long long a = A[i][k];
                for (int j = 0; j < m; ++j)
                    C[i][j] = (C[i][j] + a * B[k][j]) % MOD;
            }
        return C;
    }

    vector<vector<long long>> matpow(vector<vector<long long>> base, long long e) {
        int m = (int)base.size();
        vector<vector<long long>> R(m, vector<long long>(m, 0));
        for (int i = 0; i < m; ++i) R[i][i] = 1; // identity
        while (e > 0) {
            if (e & 1) R = matmul(R, base);
            base = matmul(base, base);
            e >>= 1;
        }
        return R;
    }
};
