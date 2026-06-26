/*
 * LeetCode 220 - Contains Duplicate III
 *
 * Given an integer array nums and two integers indexDiff and valueDiff, decide
 * whether there exist two distinct indices i, j with |i - j| <= indexDiff and
 * |nums[i] - nums[j]| <= valueDiff. Return true if such a pair exists.
 *
 * Input  : vector<int>& nums, int indexDiff (>= 1), int valueDiff (>= 0).
 * Output : bool — true iff a close-in-index, close-in-value pair exists.
 *
 * Constraints: 2 <= n <= 10^5; -10^9 <= nums[i] <= 10^9; 1 <= indexDiff <= n;
 *              0 <= valueDiff <= 10^9.
 *
 * Approach: bucketing inside a sliding index window. Use buckets of width
 *   w = valueDiff + 1, so two values in the SAME bucket automatically differ by at
 *   most valueDiff. Keep only the last indexDiff elements (one value per bucket —
 *   a second value mapping to an occupied bucket is itself an answer). For each x,
 *   landing in an occupied bucket is an immediate hit; otherwise the only other way
 *   to be within valueDiff is the two neighbouring buckets, so check those by their
 *   actual stored value. After processing, drop the element that just left the
 *   index window. Bucket index is a floor division (not C++'s truncate-toward-zero)
 *   so negative values bucket correctly.
 *
 * Complexity: O(n) time — each element is inserted and erased once with O(1) hash
 *   operations. O(min(n, indexDiff)) space for the live buckets. All arithmetic is
 *   64-bit: a difference can reach 2*10^9 and w can reach 10^9 + 1.
 */

#include <vector>
#include <unordered_map>
#include <cstdlib>
using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        long long w = (long long)valueDiff + 1;     // bucket width; same bucket => within valueDiff
        unordered_map<long long, long long> bucket;  // bucket index -> the value living there

        for (int i = 0; i < (int)nums.size(); ++i) {
            long long x = nums[i];
            long long id = floorDiv(x, w);

            // Same bucket: the gap is < w = valueDiff + 1, i.e. <= valueDiff.
            if (bucket.count(id)) return true;
            // Neighbouring buckets can still be within valueDiff — verify by value.
            auto lo = bucket.find(id - 1);
            if (lo != bucket.end() && llabs(x - lo->second) <= valueDiff) return true;
            auto hi = bucket.find(id + 1);
            if (hi != bucket.end() && llabs(x - hi->second) <= valueDiff) return true;

            bucket[id] = x;

            // Evict the element now indexDiff+1 positions back: it left the window.
            if (i >= indexDiff)
                bucket.erase(floorDiv((long long)nums[i - indexDiff], w));
        }
        return false;
    }

private:
    // Floor division for divisor b > 0 (C++ '/' truncates toward zero, which would
    // misbucket negatives: -5 / 4 == -1, but the floor we need is -2).
    static long long floorDiv(long long a, long long b) {
        long long q = a / b;
        if (a % b != 0 && a < 0) --q;
        return q;
    }
};
