/*
 * LeetCode 19 - Remove Nth Node From End of List
 *
 * Given the head of a singly linked list, remove the n-th node counting from the
 * end of the list and return the head of the resulting list.
 *
 * Input  : ListNode* head, int n. Output : head of the list after removal.
 * Constraints: list size sz with 1 <= sz <= 30; 0 <= Node.val <= 100; 1 <= n <= sz.
 *
 * Approach: a single-pass two-pointer scan with a dummy node placed before the
 *   head, which removes the special case of deleting the first node. Advance a
 *   fast pointer n + 1 steps from the dummy so that fast and a slow pointer (also
 *   starting at the dummy) stay n + 1 nodes apart. Then move both in lockstep
 *   until fast runs off the end; at that moment slow sits on the node immediately
 *   before the n-th-from-last, so its successor is the node to drop. Unlink and
 *   delete that successor, and return dummy.next, which is the correct head even
 *   when the original head was the node removed. One traversal answers the
 *   "could you do it in one pass" follow-up.
 *
 * Complexity: O(sz) time (one pass), O(1) extra space.
 */

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);               // sentinel so head removal is uniform
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Open a gap of n + 1 nodes: after this, fast leads slow by n + 1.
        for (int i = 0; i <= n; ++i)
            fast = fast->next;

        // Walk both until fast falls off the end; slow stops before the target.
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        // slow->next is the n-th node from the end: unlink and free it.
        ListNode* target = slow->next;
        slow->next = target->next;
        delete target;

        return dummy.next;                     // correct head even if it changed
    }
};
