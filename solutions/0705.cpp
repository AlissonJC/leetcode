/*
 * LeetCode 705 - Design HashSet
 *
 * Design a set of integer keys without using any built-in hash-table library.
 * Implement MyHashSet:
 *   MyHashSet()          - create an empty set.
 *   add(int key)         - insert key (a no-op if already present).
 *   contains(int key)    - return whether key is in the set.
 *   remove(int key)      - delete key if present; otherwise do nothing.
 *
 * Input/Output: a sequence of method calls; contains() returns a bool.
 *
 * Constraints: 0 <= key <= 1e6; at most 1e4 calls across the operations.
 *
 * Approach: a hash set with separate chaining. Keep a fixed array of buckets
 *   whose count is a prime (769) so that key % count scatters keys evenly, and
 *   let each bucket hold a linked list of keys. Every operation hashes the key to
 *   its bucket and scans that one short chain: add appends only if the key is not
 *   already there, contains reports whether the scan found it, and remove unlinks
 *   the matching node. With at most 1e4 keys over 769 buckets the chains stay
 *   tiny, so each operation is O(1) on average.
 *
 * Complexity: O(1) average per operation (O(chain length) worst case within a
 *   bucket); O(n + B) space for n stored keys and B buckets.
 */

#include <vector>
#include <list>
using namespace std;

class MyHashSet {
private:
    static const int NUM_BUCKETS = 769;          // prime bucket count spreads keys
    vector<list<int>> buckets;

    int bucketOf(int key) const { return key % NUM_BUCKETS; }

public:
    MyHashSet() : buckets(NUM_BUCKETS) {}

    void add(int key) {
        auto& chain = buckets[bucketOf(key)];
        for (int k : chain)
            if (k == key) return;                // already present: nothing to do
        chain.push_back(key);                    // new key: append to the chain
    }

    bool contains(int key) {
        const auto& chain = buckets[bucketOf(key)];
        for (int k : chain)
            if (k == key) return true;
        return false;
    }

    void remove(int key) {
        auto& chain = buckets[bucketOf(key)];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == key) {                    // found -> unlink and stop
                chain.erase(it);
                return;
            }
        }
    }
};
