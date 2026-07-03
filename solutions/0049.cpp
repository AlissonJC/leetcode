/*
 * LeetCode 49 - Group Anagrams
 *
 * Given an array of strings, group together the ones that are anagrams of each
 * other. Two strings are anagrams when one is a rearrangement of the other -
 * that is, they contain exactly the same letters with the same multiplicities.
 * The groups, and the strings within each group, may be returned in any order.
 *
 * Input  : vector<string> strs - the words to group.
 * Output : vector<vector<string>> - each inner vector is one anagram class.
 *
 * Constraints: 1 <= strs.length <= 10^4; 0 <= strs[i].length <= 100;
 *   strs[i] consists of lowercase English letters only.
 *
 * Approach: give every string a canonical signature that is identical for
 *   anagrams and different otherwise, then bucket the strings by that signature
 *   in a hash map. Sorting the characters would work, but since the alphabet is
 *   just the 26 lowercase letters, a letter-count fingerprint is cheaper and
 *   just as unique: build a 26-byte string whose position c stores how many
 *   times letter c occurs. Anagrams produce byte-identical keys, non-anagrams
 *   differ in at least one count. One left-to-right pass drops each word into
 *   its bucket; afterward the buckets are the answer. Counts never exceed the
 *   max length 100, which fits comfortably in a single char.
 *
 * Complexity: O(sum of |strs[i]|) time - building every key is linear in the
 *   total number of characters, and hash operations are O(key length) = O(26);
 *   O(sum of |strs[i]|) space for the map keys and the grouped output.
 */

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Map a canonical 26-count signature to the list of words sharing it.
        unordered_map<string, vector<string>> buckets;

        for (const string& s : strs) {
            // Build the fingerprint: key[c] = frequency of letter ('a' + c).
            // A fixed 26-byte layout makes anagrams collide exactly, with no
            // need for separators (each letter owns one dedicated byte).
            string key(26, '\0');
            for (char ch : s) ++key[ch - 'a'];

            buckets[key].push_back(s);   // append this word to its anagram class
        }

        // Emit the buckets. The map already merged every anagram class, so just
        // move each list into the result; order is unspecified and free to vary.
        vector<vector<string>> result;
        result.reserve(buckets.size());
        for (auto& [key, group] : buckets)
            result.push_back(move(group));
        return result;
    }
};
