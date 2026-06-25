/*
 * LeetCode 706 - Design HashMap
 *
 * Design a key-to-value map for integer keys without using any built-in
 * hash-table library. Implement MyHashMap:
 *   MyHashMap()              - create an empty map.
 *   put(int key, int value)  - insert the pair, or overwrite the value if the
 *                              key already exists.
 *   get(int key)             - return the value mapped to key, or -1 if absent.
 *   remove(int key)          - delete key and its value if present.
 *
 * Input/Output: a sequence of method calls; get() returns the stored value or -1.
 *
 * Constraints: 0 <= key, value <= 1e6; at most 1e4 calls across the operations.
 *
 * Approach: a hash table with separate chaining. Keep a fixed array of buckets
 *   whose count is a prime (769) so that key % count scatters keys evenly, and
 *   let each bucket hold a linked list of (key, value) pairs. Every operation
 *   hashes the key to its bucket and then walks that one short chain: put scans
 *   for the key to overwrite (or appends a new pair), get returns the matching
 *   value (or -1), and remove erases the matching node. With at most 1e4 keys
 *   spread over 769 buckets the chains stay tiny, so operations are O(1) on
 *   average.
 *
 * Complexity: O(1) average per operation (O(chain length) worst case within a
 *   bucket); O(n + B) space for n stored pairs and B buckets.
 */

#include <vector>
#include <list>
#include <utility>
using namespace std;

class MyHashMap {
private:
    static const int NUM_BUCKETS = 769;          // prime bucket count spreads keys
    vector<list<pair<int, int>>> buckets;

    int bucketOf(int key) const { return key % NUM_BUCKETS; }

public:
    MyHashMap() : buckets(NUM_BUCKETS) {}

    void put(int key, int value) {
        auto& chain = buckets[bucketOf(key)];
        for (auto& kv : chain) {
            if (kv.first == key) {               // key exists -> overwrite value
                kv.second = value;
                return;
            }
        }
        chain.emplace_back(key, value);          // new key -> append to the chain
    }

    int get(int key) {
        const auto& chain = buckets[bucketOf(key)];
        for (const auto& kv : chain) {
            if (kv.first == key) return kv.second;
        }
        return -1;                               // key not present
    }

    void remove(int key) {
        auto& chain = buckets[bucketOf(key)];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {              // found -> unlink and stop
                chain.erase(it);
                return;
            }
        }
    }
};
