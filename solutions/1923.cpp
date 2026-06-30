/*
 * LeetCode 1923 - Longest Common Subpath
 *
 * There are m friends, each travelling along a path given as a sequence of city ids
 * in [0, n). A subpath is a contiguous slice of a path. Return the length of the
 * longest subpath shared by EVERY friend's path, or 0 if the paths share nothing.
 * In other words: the longest common substring across m integer sequences.
 *
 * Input  : int n (number of cities); vector<vector<int>> paths (the m sequences).
 * Output : int — length of the longest subpath common to all paths.
 *
 * Constraints: 1 <= n <= 1e5; 2 <= m <= 1e5; sum of all path lengths <= 1e5;
 *   0 <= paths[i][j] < n; no city repeats consecutively within a path. The total
 *   amount of data is bounded by 1e5, so the budget is roughly O(total * log).
 *
 * Approach: binary-search the answer length L. "Some length-L subpath is common to
 *   all paths" is monotonic — shortening a common subpath by one city keeps it common —
 *   so the largest feasible L can be found by binary search over [1, minLen]. To test a
 *   given L with Rabin-Karp rolling hashes: hash every length-L window of the shortest
 *   path into a set, then for each remaining path keep only the window hashes already in
 *   the set; if the running intersection ever empties, L is infeasible, otherwise it is.
 *   Polynomial prefix hashes make each window hash O(1).
 *
 *   Collision control: a single ~1e9 hash would almost certainly collide across up to
 *   1e5 windows, so two independent moduli are combined into one 64-bit key, and the
 *   bases are randomized at run time to neutralize adversarial (anti-hash) test data.
 *
 * Complexity: O(total * log(minLen)) time, where total = sum of path lengths;
 *   O(total) space for the prefix hashes and the working sets.
 */

#include <vector>
#include <unordered_set>
#include <random>
#include <chrono>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    const long long M1 = 1000000007LL, M2 = 1000000009LL;
    long long B1, B2;                          // randomized bases
    vector<vector<long long>> pre1, pre2;      // per-path polynomial prefix hashes
    vector<long long> pow1, pow2;              // base powers
    vector<vector<int>>* P = nullptr;
    int m = 0, seedIdx = 0;                    // seedIdx = index of the shortest path

    // Combined double-hash key of the window paths[p][l .. l+L-1].
    unsigned long long windowKey(int p, int l, int L) {
        long long h1 = ((pre1[p][l + L] - pre1[p][l] * pow1[L]) % M1 + M1) % M1;
        long long h2 = ((pre2[p][l + L] - pre2[p][l] * pow2[L]) % M2 + M2) % M2;
        return (unsigned long long)h1 * (unsigned long long)M2 + (unsigned long long)h2;
    }

    // Is there a length-L subpath present in every path?
    bool check(int L) {
        if (L == 0) return true;
        auto& paths = *P;

        // Seed the candidate set with every length-L window of the shortest path.
        unordered_set<unsigned long long> cur;
        int sn = (int)paths[seedIdx].size();
        cur.reserve((size_t)(sn - L + 1) * 2);
        for (int l = 0; l + L <= sn; ++l) cur.insert(windowKey(seedIdx, l, L));
        if (cur.empty()) return false;

        // Intersect against every other path; the candidate set only shrinks.
        for (int p = 0; p < m; ++p) {
            if (p == seedIdx) continue;
            unordered_set<unsigned long long> nxt;
            int len = (int)paths[p].size();
            for (int l = 0; l + L <= len; ++l) {
                unsigned long long k = windowKey(p, l, L);
                if (cur.count(k)) nxt.insert(k);
            }
            if (nxt.empty()) return false;      // this path kills every candidate
            cur.swap(nxt);
        }
        return !cur.empty();
    }

    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        P = &paths;
        m = (int)paths.size();

        int minLen = INT_MAX, maxLen = 0;
        for (int i = 0; i < m; ++i) {
            int len = (int)paths[i].size();
            if (len < minLen) { minLen = len; seedIdx = i; }  // start from the shortest
            maxLen = max(maxLen, len);
        }

        // Random bases so no fixed input can be crafted to force hash collisions.
        mt19937_64 rng((unsigned long long)
                       chrono::steady_clock::now().time_since_epoch().count());
        B1 = (long long)(rng() % (M1 - 256)) + 256;
        B2 = (long long)(rng() % (M2 - 256)) + 256;

        pow1.assign(maxLen + 1, 1);
        pow2.assign(maxLen + 1, 1);
        for (int i = 1; i <= maxLen; ++i) {
            pow1[i] = pow1[i - 1] * B1 % M1;
            pow2[i] = pow2[i - 1] * B2 % M2;
        }

        // Prefix hashes; cities are stored as (city + 1) so that city 0 is not a no-op.
        pre1.assign(m, {});
        pre2.assign(m, {});
        for (int i = 0; i < m; ++i) {
            int len = (int)paths[i].size();
            pre1[i].assign(len + 1, 0);
            pre2[i].assign(len + 1, 0);
            for (int j = 0; j < len; ++j) {
                long long v = paths[i][j] + 1;
                pre1[i][j + 1] = (pre1[i][j] * B1 + v) % M1;
                pre2[i][j + 1] = (pre2[i][j] * B2 + v) % M2;
            }
        }

        // Largest L in [1, minLen] that is feasible; 0 if even length 1 is not shared.
        int lo = 1, hi = minLen, ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (check(mid)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    }
};
