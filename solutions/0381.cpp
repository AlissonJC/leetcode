/*
 * LeetCode 381 - Insert Delete GetRandom O(1) - Duplicates allowed
 *
 * Design a multiset (duplicates allowed) supporting three average-O(1) operations:
 *   insert(val)  - add one copy of val; return true iff val was not already present.
 *   remove(val)  - delete one copy of val if any; return true iff a copy existed.
 *   getRandom()  - return a random element; each element is returned with probability
 *                  proportional to its multiplicity (so a value present k times is k times
 *                  as likely).
 *
 * Input  : a sequence of RandomizedCollection(), insert, remove, getRandom calls.
 * Output : insert/remove return bool; getRandom returns one stored value.
 *
 * Constraints: -2^31 <= val <= 2^31 - 1; up to 2e5 total calls; getRandom only on a
 *   non-empty collection.
 *
 * Approach: extend the single-value trick (problem 380) to a multiset. Keep a dense vector
 *   `data` of every element including duplicates, so getRandom is one uniform index pick
 *   whose distribution is automatically proportional to multiplicity. Because a value can
 *   occupy many positions, map each value to the *set* of indices it holds:
 *   unordered_map<int, unordered_set<int>>. Insertion appends and records the new index.
 *   Deletion keeps the vector dense by moving the last element into the vacated slot, but
 *   the order of bookkeeping matters: first erase the chosen index from the target value's
 *   set, and only perform the swap when that index is not already the last slot. Doing it
 *   in this order avoids the classic bug where the last element equals the value being
 *   removed and a single-copy delete corrupts the index set.
 *
 * Complexity: insert/remove/getRandom all average O(1) (hash set begin/insert/erase are
 *   amortized O(1)); O(n) space.
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
using namespace std;

class RandomizedCollection {
    vector<int> data;                             // every element, duplicates included
    unordered_map<int, unordered_set<int>> where; // value -> set of its indices in `data`
    mt19937 rng;                                  // random engine for getRandom

public:
    RandomizedCollection() : rng(random_device{}()) {}

    bool insert(int val) {
        bool wasAbsent = where[val].empty();      // empty set (new or emptied) => not present
        where[val].insert((int)data.size());      // record the position of the new copy
        data.push_back(val);
        return wasAbsent;
    }

    bool remove(int val) {
        auto it = where.find(val);
        if (it == where.end() || it->second.empty())
            return false;                         // no copy of val to remove

        int removeIdx = *it->second.begin();      // an arbitrary position holding val
        it->second.erase(removeIdx);              // drop this occurrence's index FIRST

        int lastIdx = (int)data.size() - 1;
        if (removeIdx != lastIdx) {
            // Move the last element into the hole and repair its recorded index. Skipping
            // this when removeIdx == lastIdx is what keeps the "last element is val" case
            // from re-adding the index we just erased.
            int lastVal = data[lastIdx];
            data[removeIdx] = lastVal;
            where[lastVal].erase(lastIdx);
            where[lastVal].insert(removeIdx);
        }
        data.pop_back();
        return true;
    }

    int getRandom() {
        // Non-empty by guarantee; a uniform index gives multiplicity-weighted values.
        uniform_int_distribution<size_t> dist(0, data.size() - 1);
        return data[dist(rng)];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
