/*
 * LeetCode 3934 - Smallest Unique Subarray
 *
 * Given an integer array nums, find the minimum length of a (contiguous) subarray that
 * is not identical to any other subarray. Two subarrays are identical when they have
 * the same length and equal elements at every position. Return that minimum length.
 *
 * Input  : vector<int> nums. Output : int — the smallest unique-subarray length.
 *
 * Constraints: 1 <= nums.length <= 1e5; 1 <= nums[i] <= 1e5. The whole array is always
 *   unique (it is the only subarray of its length), so an answer in [1, n] always exists.
 *
 * Approach: "some length-L subarray is unique" is monotonic in L. If a unique subarray
 *   of length L < n sits at index i, extend it by one element (to the right if it fits,
 *   otherwise to the left): any duplicate of the longer block would contain a duplicate
 *   of the original block, which is impossible — so a unique subarray of length L+1 also
 *   exists. Therefore binary-search the smallest feasible L. To test a length L, hash
 *   every length-L window and tally the hashes; L is feasible exactly when some window
 *   hash occurs only once. Polynomial prefix hashes give each window hash in O(1).
 *
 *   Two independent moduli are combined into one 64-bit key with randomized bases.
 *   Collisions can only merge distinct windows (identical windows always share a hash),
 *   so they could only hide a unique window, never invent one — double hashing makes
 *   that practically impossible.
 *
 * Complexity: O(n log n) time (log n binary-search steps, each an O(n) tally);
 *   O(n) space for the prefix hashes and the per-check map.
 */

#include <vector>
#include <unordered_map>
#include <random>
#include <chrono>
using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        const long long M1 = 1000000007LL, M2 = 998244353LL;
        mt19937_64 rng((unsigned long long)
                       chrono::steady_clock::now().time_since_epoch().count());
        const long long B1 = (long long)(rng() % 500000) + 256;
        const long long B2 = (long long)(rng() % 500000) + 256;

        int n = (int)nums.size();
        vector<long long> p1(n + 1, 0), p2(n + 1, 0), pw1(n + 1, 1), pw2(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            long long v = nums[i];
            p1[i + 1] = (p1[i] * B1 + v) % M1;
            p2[i + 1] = (p2[i] * B2 + v) % M2;
            pw1[i + 1] = pw1[i] * B1 % M1;
            pw2[i + 1] = pw2[i] * B2 % M2;
        }
        auto win = [&](int l, int L) -> unsigned long long {
            long long a = ((p1[l + L] - p1[l] * pw1[L]) % M1 + M1) % M1;
            long long b = ((p2[l + L] - p2[l] * pw2[L]) % M2 + M2) % M2;
            return (unsigned long long)a * (unsigned long long)M2 + (unsigned long long)b;
        };

        // Feasible iff some length-L window is unique (appears exactly once).
        auto check = [&](int L) -> bool {
            unordered_map<unsigned long long, int> cnt;
            cnt.reserve((size_t)(n - L + 1) * 2);
            for (int i = 0; i + L <= n; ++i) cnt[win(i, L)]++;
            for (auto& kv : cnt) if (kv.second == 1) return true;
            return false;
        };

        // Smallest L with check(L) true; check(n) is always true (a single window).
        int lo = 1, hi = n, ans = n;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (check(mid)) { ans = mid; hi = mid - 1; }
            else lo = mid + 1;
        }
        return ans;
    }
};
