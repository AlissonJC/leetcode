/*
 * LeetCode 86 - Partition List
 *
 * Given the head of a singly linked list and a value x, reorder it so that every node with
 * value < x appears before every node with value >= x, while preserving the original
 * relative order within each of the two groups. Return the new head.
 *
 * Input  : ListNode* head (possibly empty), int x.
 * Output : head of the partitioned list.
 * Constraints: 0..200 nodes, -100 <= Node.val <= 100, -200 <= x <= 200.
 *
 * Approach: Build two separate chains, each with a dummy head and a running tail: one for
 *   nodes with value < x, one for nodes with value >= x. Walk the original list once and
 *   append each node (relinked, not copied) to the tail of its chain — appending in
 *   traversal order keeps each group's relative order intact. Finally terminate the >= chain
 *   with a null next (so its last node cannot still point back into the < chain and form a
 *   cycle) and splice the >= chain onto the end of the < chain. The < chain's dummy.next is
 *   the answer, and it correctly yields the >= chain when no node is < x.
 *
 * Complexity: O(n) time, O(1) extra space.
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
    ListNode* partition(ListNode* head, int x) {
        ListNode lessDummy(0), geDummy(0);       // sentinel heads for the two partitions
        ListNode* lessTail = &lessDummy;         // last node placed in the "< x" chain
        ListNode* geTail = &geDummy;             // last node placed in the ">= x" chain

        for (ListNode* cur = head; cur; cur = cur->next) {
            if (cur->val < x) { lessTail->next = cur; lessTail = cur; }
            else              { geTail->next = cur;   geTail = cur; }
        }

        geTail->next = nullptr;                  // cap the >= chain (prevents a dangling cycle)
        lessTail->next = geDummy.next;           // < chain first, then the >= chain
        return lessDummy.next;                   // dummy.next is the >= chain when nothing is < x
    }
};
