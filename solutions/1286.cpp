/*
 * LeetCode 1286 - Iterator for Combination
 *
 * Given a string of sorted, distinct lowercase letters and a length k, iterate over
 * every k-letter combination of those letters in lexicographic order. Because the
 * source letters are already sorted and distinct, a combination is fully described by
 * the strictly increasing tuple of the indices it selects, and lexicographic order of
 * the emitted strings is exactly lexicographic order of those index tuples.
 *
 * Input  : a sequence of CombinationIterator(characters, combinationLength), next(),
 *          hasNext() operations. All next() calls are guaranteed valid (hasNext() true).
 * Output : next() returns the next k-length combination as a string; hasNext() reports
 *          whether any combination is still left.
 *
 * Constraints: 1 <= combinationLength <= characters.length <= 15; all letters unique;
 *   up to 1e4 calls to next/hasNext.
 *
 * Approach: hold the current combination as its index tuple idx[0..k-1] (strictly
 *   increasing), starting at the lexicographically smallest 0,1,...,k-1. next() renders
 *   the current tuple, then advances it to the successor in O(k) without ever building
 *   the full list of C(n,k) combinations: find the rightmost position j that has room to
 *   grow (idx[j] can reach at most n-k+j, since the k-1-j positions after it need larger
 *   distinct indices), increment it, and repack every later position to consecutive
 *   values. When no position has room, the current tuple was the last one, so clear the
 *   "more" flag. This lazy successor walk uses O(k) memory instead of materializing all
 *   combinations (up to C(15,7) = 6435 of them).
 *
 * Complexity: next() O(k) (render + advance), hasNext() O(1); O(k) space for the index
 *   tuple (plus the stored characters).
 */

#include <string>
#include <vector>
using namespace std;

class CombinationIterator {
    string chars;      // the sorted, distinct source letters
    int n, k;          // number of letters, combination length
    vector<int> idx;   // current combination as strictly increasing indices, size k
    bool more;         // whether a not-yet-returned combination still exists

public:
    CombinationIterator(string characters, int combinationLength)
        : chars(characters),
          n((int)characters.size()),
          k(combinationLength),
          idx(combinationLength),
          more(true) {
        // Lexicographically smallest combination selects the first k indices.
        for (int i = 0; i < k; ++i)
            idx[i] = i;
    }

    string next() {
        // Render the current combination from its selected indices.
        string res;
        res.reserve(k);
        for (int i = 0; i < k; ++i)
            res += chars[idx[i]];

        // Advance idx to the next combination in lexicographic order.
        // Position j can still grow while idx[j] < n - k + j (its maximum feasible value).
        int j = k - 1;
        while (j >= 0 && idx[j] == n - k + j)
            --j;
        if (j < 0) {
            more = false;                    // just returned the final combination
        } else {
            ++idx[j];                        // bump the rightmost position that has room
            for (int t = j + 1; t < k; ++t)  // and repack the tail to consecutive indices
                idx[t] = idx[t - 1] + 1;
        }
        return res;
    }

    bool hasNext() {
        return more;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
