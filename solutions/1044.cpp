/*
 * LeetCode 1044 - Longest Duplicate Substring
 *
 * A "duplicated substring" is a contiguous substring of s that occurs two or more
 * times; the occurrences are allowed to overlap. Return any duplicated substring of
 * the maximum possible length, or "" if s has no duplicated substring at all.
 *
 * Input  : string s. Output : string — a longest duplicated substring (or "").
 *
 * Constraints: 2 <= s.length <= 3e4; s is lowercase English letters. An O(N^2) scan
 *   over all substring pairs (~1e9) would be too slow, so a suffix-array approach is
 *   used to bring the work down to O(N log^2 N).
 *
 * Approach: the longest duplicated substring equals the longest common prefix shared
 *   by two different suffixes of s — if two distinct suffixes share a prefix of length
 *   L, that length-L string begins at two positions and is therefore a duplicate. Over
 *   all suffix pairs this maximum LCP is attained by two suffixes that are ADJACENT in
 *   sorted order, so it is simply the largest entry of the LCP array of the suffix
 *   array. Build the suffix array by prefix doubling (sort suffixes by their first 1,
 *   2, 4, ... characters using rank pairs), then build the LCP array with Kasai's
 *   linear scan, and report the suffix prefix at the position of the maximum LCP.
 *
 * Complexity: O(N log^2 N) time — O(log N) doubling rounds, each an O(N log N) sort;
 *   plus O(N) for Kasai. O(N) space.
 */

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string longestDupSubstring(string s) {
        int n = (int)s.size();

        // ---- Suffix array via prefix doubling ----
        // rnk[i] = current rank (sort key) of the suffix starting at i; refined each
        // round so that it reflects ordering by the first 2^round characters.
        vector<int> sa(n), rnk(n), tmp(n);
        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            rnk[i] = (unsigned char)s[i];   // round 0: order by the single first char
        }

        for (int k = 1; k < n; k <<= 1) {
            // Compare two suffixes by (rank, rank shifted by k): the second half's rank
            // is -1 when the suffix is too short, which correctly sorts shorter first.
            auto cmp = [&](int a, int b) {
                if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
                int ra = (a + k < n) ? rnk[a + k] : -1;
                int rb = (b + k < n) ? rnk[b + k] : -1;
                return ra < rb;
            };
            sort(sa.begin(), sa.end(), cmp);

            // Re-number ranks from the freshly sorted order; equal neighbours keep the
            // same rank so the next round can distinguish them by the next 2^k chars.
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            rnk = tmp;

            if (rnk[sa[n - 1]] == n - 1) break;   // all ranks distinct -> SA is final
        }

        // ---- LCP array (Kasai) ----
        // lcp[i] = longest common prefix of the suffixes sa[i] and sa[i-1]; lcp[0] = 0.
        // `h` only ever drops by 1 between iterations, which makes the scan linear.
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[sa[i]] = i;

        int best = 0, bestStart = 0, h = 0;
        for (int i = 0; i < n; ++i) {
            if (pos[i] > 0) {
                int j = sa[pos[i] - 1];                       // suffix just before i in SA
                while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
                if (h > best) { best = h; bestStart = i; }    // track the longest LCP
                if (h > 0) --h;
            } else {
                h = 0;
            }
        }

        // best == 0 means no two suffixes share a prefix -> no duplicated substring.
        return s.substr(bestStart, best);
    }
};
