/*
 * LeetCode 2343 - Query Kth Smallest Trimmed Number
 *
 * Given a 0-indexed array of equal-length digit strings nums and a list of queries
 * [k, trim], answer each query: trim every number to its rightmost `trim` digits,
 * find the index of the k-th smallest trimmed value (ties broken by smaller
 * original index), then restore the numbers. Return one answer per query.
 *
 * Input  : vector<string>& nums, vector<vector<int>>& queries.
 * Output : vector<int> — answer[i] is the index returned for queries[i].
 *
 * Constraints: 1 <= nums.length, nums[i].length, queries.length <= 100; all
 *   nums[i] share the same length and contain only digits. Tiny sizes, so a direct
 *   sort per query easily fits the time budget.
 *
 * Approach: handle each query independently. The "rightmost trim digits" of a
 *   length-L string is its suffix substr(L - trim). Crucially, all trimmed strings
 *   in one query have the SAME length, so comparing them lexicographically is the
 *   same as comparing them numerically (leading zeros included) — "02" < "14" both
 *   as text and as numbers. Build pairs (trimmed suffix, original index) and sort
 *   them: std::pair orders by the string first and by the index second, which
 *   gives exactly the required tie-break (lower index wins on equal values). The
 *   k-th smallest sits at sorted position k-1; report its stored index.
 *
 * Complexity: O(Q * n log n * L) time (each of Q queries sorts n strings of length
 *   up to L), O(n * L) extra space per query for the suffix pairs.
 */

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int L = (int)nums[0].size();                 // common length of every number
        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int k = q[0], trim = q[1];

            // Pair each number's rightmost `trim` digits with its original index.
            // Equal-length suffixes => lexicographic order matches numeric order.
            vector<pair<string, int>> trimmed;
            trimmed.reserve(nums.size());
            for (int i = 0; i < (int)nums.size(); ++i)
                trimmed.emplace_back(nums[i].substr(L - trim), i);

            // Sort by (suffix, index): ties on the value fall back to smaller index.
            sort(trimmed.begin(), trimmed.end());

            // The k-th smallest (1-indexed) is at position k-1; report its index.
            answer.push_back(trimmed[k - 1].second);
        }

        return answer;
    }
};
