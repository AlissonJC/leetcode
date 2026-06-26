/*
 * LeetCode 347 - Top K Frequent Elements
 *
 * Given an integer array nums and an integer k, return the k values that occur
 * most often. Any order is accepted, and the answer is guaranteed unique (no tie
 * straddles the k-th place).
 *
 * Input  : vector<int>& nums, int k.
 * Output : vector<int> of the k most frequent values.
 *
 * Constraints: 1 <= n <= 10^5; -10^4 <= nums[i] <= 10^4; 1 <= k <= number of
 *              distinct values; the top-k set is unique.
 *
 * Approach: count-then-bucket, which runs in O(n) and so beats the O(n log n) that
 *   sorting by frequency would cost (the stated follow-up). First tally each value
 *   with a hash map. A value's frequency lies in 1..n, so index buckets directly by
 *   frequency: bucket[f] collects every value seen exactly f times. Finally sweep
 *   frequencies from n down to 1, emitting values until k are gathered — the first
 *   k encountered are exactly the most frequent. The uniqueness guarantee means the
 *   k-th cut never splits a bucket ambiguously.
 *
 * Complexity: O(n) time (counting, bucket fill, and the descending sweep are each
 *   linear) and O(n) space for the map and buckets.
 */

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = (int)nums.size();

        // Tally occurrences of each distinct value.
        unordered_map<int, int> freq;
        freq.reserve(n * 2);
        for (int x : nums) ++freq[x];

        // bucket[f] = values occurring exactly f times. Frequencies span 1..n,
        // so n + 1 slots cover every possible count without any sorting.
        vector<vector<int>> bucket(n + 1);
        for (const auto& kv : freq)
            bucket[kv.second].push_back(kv.first);

        // Take values from the highest frequency downward until k are collected.
        vector<int> result;
        result.reserve(k);
        for (int f = n; f >= 1 && (int)result.size() < k; --f) {
            for (int val : bucket[f]) {
                result.push_back(val);
                if ((int)result.size() == k) break;   // exactly k -> done
            }
        }
        return result;
    }
};
