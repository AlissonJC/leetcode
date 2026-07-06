/*
 * LeetCode 380 - Insert Delete GetRandom O(1)
 *
 * Design a set supporting three operations, each in average O(1) time:
 *   insert(val)  - add val if absent; return whether it was newly added.
 *   remove(val)  - delete val if present; return whether it was there.
 *   getRandom()  - return a uniformly random current element (set is non-empty when called).
 *
 * Input  : a sequence of RandomizedSet(), insert(val), remove(val), getRandom() calls.
 * Output : insert/remove return bool; getRandom returns one stored value.
 *
 * Constraints: -2^31 <= val <= 2^31 - 1; up to 2e5 total calls; getRandom only on a
 *   non-empty set.
 *
 * Approach: a hash map alone gives O(1) insert/remove but cannot pick a uniform random
 *   element in O(1); a plain array gives O(1) random indexing but O(n) deletion. Combine
 *   them: keep a dense vector `data` of the elements (so getRandom is one indexed lookup)
 *   plus a map `pos` from value to its index in that vector. Insertion appends to the end.
 *   The trick is deletion in O(1): overwrite the removed value's slot with the vector's
 *   last element, fix that element's recorded index, then pop_back — this keeps `data`
 *   contiguous without shifting, so random indexing stays valid. The swap-with-last also
 *   works when the removed value already sits last (it degenerates to a plain pop).
 *
 * Complexity: insert/remove/getRandom all average O(1); O(n) space.
 */

#include <vector>
#include <unordered_map>
#include <random>
using namespace std;

class RandomizedSet {
    vector<int> data;                // contiguous elements; enables O(1) random indexing
    unordered_map<int, int> pos;     // value -> its index inside `data`
    mt19937 rng;                     // random engine, seeded once

public:
    RandomizedSet() : rng(random_device{}()) {}

    bool insert(int val) {
        if (pos.count(val))
            return false;            // already present, nothing to do
        pos[val] = (int)data.size(); // new element goes to the end of the vector
        data.push_back(val);
        return true;
    }

    bool remove(int val) {
        auto it = pos.find(val);
        if (it == pos.end())
            return false;            // not present
        int idx = it->second;
        int lastVal = data.back();
        // Move the last element into the vacated slot and repair its index, so the vector
        // stays dense and no O(n) shifting is needed.
        data[idx] = lastVal;
        pos[lastVal] = idx;          // harmless self-assignment when val == lastVal
        data.pop_back();
        pos.erase(val);              // erase by key: correct whether or not val was last
        return true;
    }

    int getRandom() {
        // The set is guaranteed non-empty here; pick a uniform index into `data`.
        uniform_int_distribution<size_t> dist(0, data.size() - 1);
        return data[dist(rng)];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
