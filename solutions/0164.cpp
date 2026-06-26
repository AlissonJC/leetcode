/*
 * LeetCode 164 - Maximum Gap
 *
 * Given an integer array nums, return the maximum difference between two
 * successive elements once the array is sorted. If the array has fewer than two
 * elements, return 0. The algorithm must run in LINEAR time and use LINEAR extra
 * space (so a comparison sort is disallowed).
 *
 * Input  : vector<int>& nums. Output : int — the largest adjacent gap in sorted order.
 *
 * Constraints: 1 <= n <= 10^5; 0 <= nums[i] <= 10^9. Differences stay within
 *   [0, 10^9], which fits in a 32-bit int.
 *
 * Approach: pigeonhole / bucket method. Spread the n values over buckets of equal
 *   width. With min lo and max hi, the largest gap in sorted order is at least
 *   ceil((hi - lo)/(n - 1)) — the average spacing — so choose a bucket width of
 *   that size. Then any two values inside the same bucket differ by less than the
 *   bucket width, hence by less than the maximum gap; therefore the maximum gap
 *   must occur BETWEEN consecutive non-empty buckets. So only each bucket's min
 *   and max matter: scan buckets in order and take the best (current bucket min -
 *   previous bucket max). Choosing the width this way keeps the bucket count O(n).
 *
 * Complexity: O(n) time (one pass to bucket, one pass over O(n) buckets); O(n)
 *   space for the per-bucket min/max arrays.
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = (int)nums.size();
        if (n < 2)
            return 0;                                   // fewer than two elements

        int lo = *min_element(nums.begin(), nums.end());
        int hi = *max_element(nums.begin(), nums.end());
        if (lo == hi)
            return 0;                                   // all equal -> every gap is 0

        // Bucket width = ceil-ish average spacing, at least 1. This guarantees the
        // maximum gap spans two different buckets, never within one.
        int bucketSize = max(1, (hi - lo) / (n - 1));
        int numBuckets = (hi - lo) / bucketSize + 1;    // O(n) buckets

        // Track only the min and max of each bucket; INT_MAX min marks "empty".
        vector<int> bucketMin(numBuckets, INT_MAX);
        vector<int> bucketMax(numBuckets, INT_MIN);
        for (int x : nums) {
            int idx = (x - lo) / bucketSize;
            bucketMin[idx] = min(bucketMin[idx], x);
            bucketMax[idx] = max(bucketMax[idx], x);
        }

        // The answer is the largest jump from one non-empty bucket's max to the
        // next non-empty bucket's min. Seed prevMax with lo (the first non-empty
        // bucket contributes a harmless 0 gap).
        int maxGap = 0, prevMax = lo;
        for (int i = 0; i < numBuckets; ++i) {
            if (bucketMin[i] == INT_MAX)
                continue;                               // empty bucket: skip
            maxGap = max(maxGap, bucketMin[i] - prevMax);
            prevMax = bucketMax[i];
        }

        return maxGap;
    }
};
