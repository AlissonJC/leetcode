/*
 * LeetCode 1206 - Design Skiplist
 *
 * Implement a skip list from scratch (no built-in libraries):
 *   Skiplist()           - create an empty skip list.
 *   search(int target)   - return whether target is present.
 *   add(int num)         - insert num (duplicates are allowed).
 *   erase(int num)       - remove one occurrence of num; return true if it was
 *                          present, false otherwise.
 *
 * Input/Output: a sequence of method calls; search and erase return a bool.
 *
 * Constraints: 0 <= num, target <= 2e4; at most 5e4 calls across the operations.
 *
 * Approach: a skip list is a stack of sorted singly linked lists. Every value
 *   lives on level 0, and each inserted node is independently promoted to each
 *   higher level with probability 1/2 (capped at MAX_LEVEL), so the upper levels
 *   act as express lanes that skip over many nodes. Each operation walks from the
 *   topmost active level downward, moving right while the next value is smaller
 *   than the query and recording the predecessor reached on every level in an
 *   "update" array. search then inspects the level-0 successor; add creates a
 *   node with a random height and links it in after the recorded predecessors;
 *   erase locates the matched node and unlinks it from each level it occupies.
 *   Because the height distribution is geometric, a node spans about two levels
 *   on average and every walk touches O(log n) nodes.
 *
 * Complexity: O(log n) expected time per operation; O(n) expected space.
 */

#include <vector>
using namespace std;

class Skiplist {
private:
    static const int MAX_LEVEL = 16;          // ~log2(5e4); cap on node height

    struct Node {
        int val;
        vector<Node*> forward;                // forward[i] = next node on level i
        Node(int v, int height) : val(v), forward(height, nullptr) {}
    };

    Node* head;          // sentinel with MAX_LEVEL forward pointers
    int level;           // number of levels currently in use (>= 1)
    unsigned rng;        // xorshift state for deterministic random heights

    unsigned nextRandom() {
        rng ^= rng << 13;
        rng ^= rng >> 17;
        rng ^= rng << 5;
        return rng;
    }

    // Geometric height: promote while a coin flip is heads, capped at MAX_LEVEL.
    int randomHeight() {
        int h = 1;
        while ((nextRandom() & 1) && h < MAX_LEVEL) ++h;
        return h;
    }

public:
    Skiplist() {
        head = new Node(-1, MAX_LEVEL);
        level = 1;
        rng = 2463534242u;                    // fixed nonzero seed
    }

    ~Skiplist() {
        // All nodes (and the head) are threaded on level 0 — free them in order.
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->forward[0];
            delete cur;
            cur = nxt;
        }
    }

    bool search(int target) {
        Node* cur = head;
        // Descend levels; on each, advance right past values strictly smaller.
        for (int i = level - 1; i >= 0; --i)
            while (cur->forward[i] && cur->forward[i]->val < target)
                cur = cur->forward[i];
        cur = cur->forward[0];                // first node with val >= target
        return cur && cur->val == target;
    }

    void add(int num) {
        // update[i] = node after which the new value belongs on level i.
        // Levels at or above the current `level` keep head as their predecessor.
        vector<Node*> update(MAX_LEVEL, head);
        Node* cur = head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->forward[i] && cur->forward[i]->val < num)
                cur = cur->forward[i];
            update[i] = cur;
        }

        int height = randomHeight();
        if (height > level)
            level = height;                   // new top levels already point from head

        Node* node = new Node(num, height);
        for (int i = 0; i < height; ++i) {    // splice into levels 0..height-1
            node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = node;
        }
    }

    bool erase(int num) {
        vector<Node*> update(MAX_LEVEL, head);
        Node* cur = head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->forward[i] && cur->forward[i]->val < num)
                cur = cur->forward[i];
            update[i] = cur;
        }

        cur = cur->forward[0];                // leftmost candidate at value num
        if (!cur || cur->val != num) return false;

        // A node occupies a contiguous range of levels 0..(its height-1); once a
        // level's predecessor does not point at it, no higher level does either.
        for (int i = 0; i < level; ++i) {
            if (update[i]->forward[i] != cur) break;
            update[i]->forward[i] = cur->forward[i];
        }
        delete cur;

        // Shrink the active level count if the topmost lists became empty.
        while (level > 1 && head->forward[level - 1] == nullptr)
            --level;
        return true;
    }
};
