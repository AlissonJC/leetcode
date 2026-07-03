/*
 * LeetCode 61 - Rotate List
 *
 * Given the head of a singly linked list, rotate the list to the right by k
 * places: the last k nodes move to the front, preserving order. Return the head
 * of the rotated list. k may be far larger than the list length.
 *
 * Input  : ListNode* head - head of the list (may be empty); int k - number of
 *          right rotations.
 * Output : ListNode* - head of the list after rotating right by k.
 *
 * Constraints: number of nodes in [0, 500]; -100 <= Node.val <= 100;
 *   0 <= k <= 2 * 10^9.
 *
 * Approach: rotating right by the list length returns the same list, so the
 *   effect of k depends only on k mod len. Reduce k that way first (this also
 *   tames the huge k bound). What remains is a single cut: the last (k mod len)
 *   nodes detach and become the new front. Do it by first walking the list once
 *   to get its length and tail, then closing it into a ring (tail -> head).
 *   Advance len - k steps from the head... concretely, step to the node at index
 *   (len - k - 1): that becomes the new tail, its successor is the new head, and
 *   cutting the ring there completes the rotation. An empty list, a single node,
 *   or a k that is a multiple of len all mean "no change", handled directly.
 *
 * Complexity: O(len) time - at most two linear walks; O(1) extra space, only a
 *   handful of pointers (the nodes are relinked in place).
 */

// struct ListNode { int val; ListNode* next; ... }; provided by the judge.

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // Empty list or single node: rotation has no visible effect.
        if (head == nullptr || head->next == nullptr) return head;

        // Pass 1: measure the length and locate the tail.
        int len = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            ++len;
        }

        // Rotations repeat every len steps; only the remainder matters. A zero
        // remainder (k is a multiple of len) leaves the list untouched.
        k %= len;
        if (k == 0) return head;

        // The node at index (len - k - 1) becomes the new tail; the node after
        // it is the new head.
        ListNode* newTail = head;
        for (int i = 0; i < len - k - 1; ++i) newTail = newTail->next;
        ListNode* newHead = newTail->next;

        // Sever between new tail and new head, and reconnect old tail to old head.
        newTail->next = nullptr;
        tail->next = head;

        return newHead;
    }
};
