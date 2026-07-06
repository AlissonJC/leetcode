/*
 * LeetCode 710 - Random Pick with Blacklist
 *
 * Given n and a list of blacklisted integers, pick() must return a uniformly random
 * integer in [0, n) that is not blacklisted, using as few RNG calls as possible.
 *
 * Input  : a sequence of Solution(n, blacklist), pick() calls.
 * Output : pick() returns a whitelisted integer in [0, n), each equally likely.
 *
 * Constraints: 1 <= n <= 1e9; 0 <= blacklist.length <= min(1e5, n-1); blacklist values
 *   are distinct and in [0, n); up to 2e4 calls to pick.
 *
 * Approach: there are valid = n - m whitelisted numbers (m = |blacklist|). Compress the
 *   pickable space to [0, valid) and draw a single random number there per pick. Numbers
 *   in [0, valid) that are whitelisted map to themselves; the blacklisted ones in that
 *   prefix are redirected to the whitelisted numbers living in the tail [valid, n). A
 *   counting argument shows the count of blacklisted numbers below valid equals the count
 *   of whitelisted numbers at or above valid, so pairing them up forms a bijection from
 *   [0, valid) onto the whole whitelist. Drawing uniformly from [0, valid) and following
 *   that map therefore yields a uniform whitelisted value with exactly one RNG call.
 *
 * Complexity: O(m) construction; O(1) average per pick (one RNG draw + one hash lookup);
 *   O(m) space.
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
using namespace std;

class Solution {
    int valid;                        // number of whitelisted values; compressed range [0, valid)
    unordered_map<int, int> remap;    // blacklisted x in [0, valid) -> a whitelisted value in [valid, n)
    mt19937 rng;                      // random engine, seeded once

public:
    Solution(int n, vector<int>& blacklist) : rng(random_device{}()) {
        int m = (int)blacklist.size();
        valid = n - m;

        unordered_set<int> black(blacklist.begin(), blacklist.end());

        // Redirect each blacklisted number that falls in the compressed prefix [0, valid)
        // to the next whitelisted number in the tail [valid, n).
        int target = valid;
        for (int b : blacklist) {
            if (b < valid) {
                while (black.count(target))   // skip blacklisted tail numbers
                    ++target;
                remap[b] = target;
                ++target;
            }
        }
    }

    int pick() {
        // One RNG draw into the compressed range, then follow the remap if needed.
        int x = uniform_int_distribution<int>(0, valid - 1)(rng);
        auto it = remap.find(x);
        return it == remap.end() ? x : it->second;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
