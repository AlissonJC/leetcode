/*
 * LeetCode 382 - Linked List Random Node
 *
 * Given the head of a singly-linked list, support getRandom(): return the value
 * of a node chosen uniformly at random, every node equally likely. The list is
 * fixed after construction; getRandom() may be called many times.
 *
 * Interface:
 *   Solution(ListNode* head) - store the list.
 *   getRandom()              - return one node's value, each with probability 1/n.
 *
 * Constraints: 1 <= n <= 10^4 nodes; -10^4 <= Node.val <= 10^4; up to 10^4 calls.
 *
 * Approach: reservoir sampling (Algorithm R) with a reservoir of size one. Walk
 *   the list once, keeping a running count of nodes seen. When the i-th node is
 *   reached, adopt its value as the current pick with probability 1/i; otherwise
 *   keep the previous pick. After the full pass the held value is uniform: the
 *   i-th node ends as the answer with probability (1/i) * prod_{j=i+1..n}(1 - 1/j)
 *   = (1/i) * (i/n) = 1/n. This needs no knowledge of the length up front and uses
 *   only a couple of variables, which is exactly what the two follow-ups ask for
 *   (extremely large list of unknown length, and no extra space beyond O(1)).
 *
 * Complexity: O(n) time per getRandom() call (one traversal); O(1) extra space.
 *   The list itself is borrowed, not copied.
 */

#include <random>
using namespace std;

// Definition for singly-linked list (provided by LeetCode):
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
public:
    // Keep only the head pointer; sampling is done lazily on each call so the
    // length never has to be stored or known ahead of time.
    Solution(ListNode* head) : head(head), gen(random_device{}()) {}

    int getRandom() {
        int result = head->val;   // n >= 1, so the head always seeds the pick
        int count = 1;            // number of nodes seen so far (the head)

        for (ListNode* node = head->next; node != nullptr; node = node->next) {
            ++count;
            // Replace the current pick with this node's value with probability
            // 1/count. uniform_int_distribution(0, count-1) hits 0 exactly that
            // often, with no modulo bias.
            if (uniform_int_distribution<int>(0, count - 1)(gen) == 0)
                result = node->val;
        }
        return result;
    }

private:
    ListNode* head;   // borrowed list, never modified
    mt19937 gen;      // pseudo-random engine, seeded once at construction
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
