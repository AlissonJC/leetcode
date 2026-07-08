/*
 * LeetCode 1207 - Unique Number of Occurrences
 *
 * Given an integer array arr, return true if the number of occurrences of each
 * distinct value is itself unique across values — i.e. no two different values appear
 * the same number of times — and false otherwise.
 *
 * Input  : vector<int>& arr.
 * Output : bool — whether all per-value occurrence counts are distinct.
 *
 * Constraints: 1 <= arr.length <= 1000, -1000 <= arr[i] <= 1000.
 *
 * Approach: Two passes with hashing. First tally how many times each value occurs into
 *   a frequency map. Then feed those counts into a set: the counts are all distinct
 *   exactly when every insertion is new, so the first insertion that collides means two
 *   values share an occurrence count and the answer is false.
 *
 * Complexity: O(n) time, O(k) space where k is the number of distinct values (<= n).
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freq;
        for (int x : arr) ++freq[x];            // freq[value] = how many times it appears

        // Collect the counts; a failed insert (second == false) means this count was
        // already produced by another value, so the occurrence counts are not unique.
        unordered_set<int> seen;
        for (const auto& [value, count] : freq)
            if (!seen.insert(count).second)
                return false;
        return true;
    }
};
