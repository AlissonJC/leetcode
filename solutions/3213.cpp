/*
 * LeetCode 3213 - Construct String with Minimum Cost
 *
 * Starting from an empty string s, repeatedly append some words[i] (paying costs[i])
 * until s equals target. Return the minimum total cost, or -1 if target cannot be
 * formed. Equivalently: tile target from left to right, where placing words[i] at the
 * current position is allowed only if it matches the target there, and costs costs[i].
 *
 * Input  : string target; vector<string> words; vector<int> costs (|words| == |costs|).
 * Output : int — minimum cost, or -1 if impossible.
 *
 * Constraints: 1 <= target.length <= 5e4; 1 <= |words| == |costs| <= 5e4;
 *   1 <= words[i].length <= target.length; sum of all words[i].length <= 5e4;
 *   1 <= costs[i] <= 1e4. Max achievable cost is 5e4 * 1e4 = 5e8.
 *
 * Approach: dp[i] = minimum cost to construct the prefix target[0..i). dp[0] = 0, and
 *   from any reachable i, for every word w that matches target starting at i, relax
 *   dp[i + |w|] with dp[i] + cost(w). The bottleneck is "which words match at i". The
 *   key observation: because the total length of all words is <= 5e4, the number of
 *   DISTINCT word lengths D satisfies 1 + 2 + ... + D <= 5e4, so D <= ~316. Group the
 *   words by length, keeping the minimum cost for each (length, content); represent
 *   content by a hash. Then at each i, probe only the D distinct lengths: hash
 *   target[i..i+L) in O(1) via prefix hashes and look it up among the length-L words.
 *   That makes the work O(n * D) instead of O(n * |words|).
 *
 *   Hashing uses two moduli combined into one 64-bit key, with randomized bases, so no
 *   crafted input can force collisions.
 *
 * Complexity: O((n + sum|words|) + n * D) time, with D = number of distinct word
 *   lengths (<= ~316); O(n + |words|) space.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        const long long M1 = 1000000007LL, M2 = 998244353LL;
        // Randomize the polynomial bases to defeat any adversarial anti-hash input.
        mt19937_64 rng((unsigned long long)
                       chrono::steady_clock::now().time_since_epoch().count());
        const long long B1 = (long long)(rng() % 200000) + 256;
        const long long B2 = (long long)(rng() % 200000) + 256;

        int n = (int)target.size();

        // Prefix hashes of target (two systems) plus base powers, for O(1) substrings.
        vector<long long> p1(n + 1, 0), p2(n + 1, 0), pw1(n + 1, 1), pw2(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            long long v = target[i] - 'a' + 1;       // +1 so 'a' is not a hashing no-op
            p1[i + 1] = (p1[i] * B1 + v) % M1;
            p2[i + 1] = (p2[i] * B2 + v) % M2;
            pw1[i + 1] = pw1[i] * B1 % M1;
            pw2[i + 1] = pw2[i] * B2 % M2;
        }
        auto sub = [&](int l, int L) -> unsigned long long {
            long long a = ((p1[l + L] - p1[l] * pw1[L]) % M1 + M1) % M1;
            long long b = ((p2[l + L] - p2[l] * pw2[L]) % M2 + M2) % M2;
            return (unsigned long long)a * (unsigned long long)M2 + (unsigned long long)b;
        };

        // Bucket words by length; within each length keep the cheapest cost per content.
        unordered_map<int, unordered_map<unsigned long long, int>> byLen;
        for (size_t k = 0; k < words.size(); ++k) {
            int L = (int)words[k].size();
            if (L > n) continue;                      // longer than target: never usable
            long long a = 0, b = 0;
            for (char c : words[k]) {
                long long v = c - 'a' + 1;
                a = (a * B1 + v) % M1;
                b = (b * B2 + v) % M2;
            }
            unsigned long long key = (unsigned long long)a * (unsigned long long)M2
                                   + (unsigned long long)b;
            auto& mp = byLen[L];
            auto it = mp.find(key);
            if (it == mp.end() || costs[k] < it->second) mp[key] = costs[k];
        }

        // Flatten to (length, map*) so the DP iterates distinct lengths without re-hashing L.
        vector<pair<int, unordered_map<unsigned long long, int>*>> groups;
        groups.reserve(byLen.size());
        for (auto& kv : byLen) groups.push_back({kv.first, &kv.second});

        const long long INF = LLONG_MAX / 2;
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (dp[i] >= INF) continue;               // prefix of length i unreachable
            for (auto& g : groups) {
                int L = g.first;
                if (i + L > n) continue;
                auto it = g.second->find(sub(i, L));  // does a length-L word match here?
                if (it != g.second->end()) {
                    long long nc = dp[i] + it->second;
                    if (nc < dp[i + L]) dp[i + L] = nc;
                }
            }
        }

        return dp[n] >= INF ? -1 : (int)dp[n];
    }
};
