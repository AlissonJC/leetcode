/*
 * LeetCode 692 - Top K Frequent Words
 *
 * Given an array of words and an integer k, return the k most frequent words,
 * ordered by frequency from highest to lowest; words sharing a frequency are
 * ordered lexicographically (ascending).
 *
 * Input  : vector<string>& words, int k.
 * Output : vector<string> — the k most frequent words in the required order.
 *
 * Constraints: 1 <= words.length <= 500; 1 <= words[i].length <= 10; lowercase
 *              letters; 1 <= k <= number of distinct words.
 *
 * Approach: count frequencies, then keep only the best k in a bounded heap, which
 *   gives the O(n log k) time and O(n) space the follow-up asks for. Rank a word as
 *   "better" when it has higher frequency, or — on a tie — is lexicographically
 *   smaller. Use a size-k priority queue whose comparator places the WORST current
 *   candidate at the top, so when the heap exceeds k that worst one is popped. After
 *   all distinct words are processed the heap holds the answer, but popping yields
 *   worst-first; fill the output array back to front to land on frequency-descending,
 *   lexicographically-ascending order.
 *
 * Complexity: O(n) to count plus O(u log k) to sift u distinct words through the
 *   size-k heap (string compares are O(10) = O(1)); O(n) space.
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
using namespace std;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // Tally how often each distinct word occurs.
        unordered_map<string, int> freq;
        for (const string& w : words) ++freq[w];

        // "a better than b" = higher frequency, or equal frequency with a
        // lexicographically smaller word. priority_queue treats the comparator as
        // "less", so the better elements sink and the WORST candidate sits on top()
        // — exactly the one to drop once the heap grows past k.
        auto betterIsLower = [](const pair<int, string>& a, const pair<int, string>& b) {
            if (a.first != b.first) return a.first > b.first;   // more frequent ranks higher
            return a.second < b.second;                          // tie: lexicographically smaller ranks higher
        };
        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(betterIsLower)> pq(betterIsLower);

        for (const auto& kv : freq) {
            pq.push({kv.second, kv.first});
            if ((int)pq.size() > k) pq.pop();   // evict the worst, retain best k
        }

        // The heap surrenders the worst first, so write from the last slot backward.
        vector<string> result(k);
        for (int i = k - 1; i >= 0; --i) {
            result[i] = pq.top().second;
            pq.pop();
        }
        return result;
    }
};
