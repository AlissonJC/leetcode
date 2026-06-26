/*
 * LeetCode 519 - Random Flip Matrix
 *
 * An m x n grid starts all zeros. flip() must pick a uniformly random still-zero
 * cell, set it to one, and return its [row, col]; every remaining zero cell must
 * be equally likely. reset() clears the grid back to all zeros. The goal is few
 * random-function calls and low time/space, even though m*n can be huge.
 *
 * Interface:
 *   Solution(int m, int n) - grid dimensions; all cells start free (zero).
 *   flip()                 - return a random free cell [i, j] and occupy it.
 *   reset()                - mark every cell free again.
 *
 * Constraints: 1 <= m, n <= 10^4 (so up to 10^8 cells); each flip has at least one
 *   free cell; at most 1000 calls total to flip and reset.
 *
 * Approach: a virtual Fisher-Yates shuffle backed by a hash map, so nothing of
 *   size m*n is ever allocated. Flatten each cell to an id in [0, total) via
 *   id -> (id / n, id % n). Keep `remaining` = number of free cells and a map
 *   `moved` that records where a logical slot has been redirected (the only slots
 *   that ever differ from their own index). A flip draws one random x in
 *   [0, remaining-1], reads the id sitting at slot x (moved[x] if present, else x),
 *   then overwrites slot x with the id from the last active slot and shrinks the
 *   pool by one. That removes the chosen id from future draws while keeping every
 *   survivor reachable — exactly Fisher-Yates selection, but only touched slots are
 *   stored. Uses a single random call per flip; reset() just empties the map.
 *
 * Complexity: flip() and reset() are O(1) amortized (reset clears a map holding at
 *   most ~1000 entries, since flips between resets are bounded by the 1000-call
 *   limit). Space is O(number of flips), never O(m*n).
 */

#include <vector>
#include <unordered_map>
#include <random>
using namespace std;

class Solution {
public:
    Solution(int m, int n)
        : cols(n), total(m * n), remaining(m * n), gen(random_device{}()) {}

    vector<int> flip() {
        // One random draw over the current free pool [0, remaining-1].
        int x = uniform_int_distribution<int>(0, remaining - 1)(gen);
        --remaining;                       // `remaining` now indexes the last slot

        // The id currently sitting at slot x (redirected if it was moved before).
        auto it = moved.find(x);
        int id = (it != moved.end()) ? it->second : x;

        // Pull the last active slot's id into slot x so x stays usable next time,
        // which logically deletes the chosen id from the pool.
        auto last = moved.find(remaining);
        moved[x] = (last != moved.end()) ? last->second : remaining;

        return { id / cols, id % cols };   // decode flat id back to [row, col]
    }

    void reset() {
        // Every cell free again: forget all redirects and restore the full pool.
        moved.clear();
        remaining = total;
    }

private:
    int cols;                          // n, used to decode flat ids into [row, col]
    int total;                         // m * n, the full free-cell count
    int remaining;                     // current number of free cells
    unordered_map<int, int> moved;     // sparse Fisher-Yates redirects
    mt19937 gen;                       // pseudo-random engine, seeded once
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */
