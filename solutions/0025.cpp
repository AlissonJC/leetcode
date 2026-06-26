/*
 * LeetCode 25 - Reverse Nodes in k-Group
 *
 * Given the head of a singly-linked list, reverse its nodes k at a time and return
 * the resulting list. If the final chunk has fewer than k nodes it is left in its
 * original order. Only the node links may change -- values must not be altered.
 * This is the general-k version of problem 24, which is exactly the k = 2 case.
 *
 * Input  : ListNode* head, int k. Output : head of the k-group-reversed list.
 * Constraints: 1 <= k <= n <= 5000, 0 <= Node.val <= 1000.
 *
 * Approach: iterate chunk by chunk with a dummy node and a `groupPrev` pointer
 *   that sits just before the chunk currently being reversed. For each chunk, walk
 *   k steps to locate its last node (kth); if fewer than k nodes remain, stop and
 *   leave that tail untouched. Otherwise reverse the chunk's links in place with
 *   the classic three-pointer reversal, seeding `prev` with the node *after* the
 *   chunk so the chunk's old head ends up linked to the rest of the list once it
 *   becomes the tail. Then reconnect: groupPrev->next becomes kth (the chunk's new
 *   head) and groupPrev advances to the chunk's old head, now its tail. No buffers
 *   are used, so this meets the O(1) extra-memory follow-up.
 *
 * Complexity: O(n) time (each node is touched a constant number of times),
 *   O(1) extra space.
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy;                 // sentinel before head; dummy.next is the answer
        dummy.next = head;
        ListNode* groupPrev = &dummy;   // node immediately before the chunk to reverse

        while (true) {
            // Locate the k-th node of this chunk by walking k steps from groupPrev.
            ListNode* kth = groupPrev;
            for (int i = 0; i < k && kth; ++i) kth = kth->next;
            if (!kth) break;            // fewer than k nodes remain -> leave them as is

            ListNode* groupNext = kth->next;   // first node beyond this chunk

            // Reverse the chunk's links. Seeding prev = groupNext makes the chunk's
            // old head point at the rest of the list once it becomes the tail.
            ListNode* prev = groupNext;
            ListNode* cur  = groupPrev->next;
            while (cur != groupNext) {
                ListNode* nxt = cur->next;
                cur->next = prev;
                prev = cur;
                cur  = nxt;
            }

            // Splice the reversed chunk in: kth is its new head, and the old head
            // (now the tail) becomes groupPrev for the next chunk.
            ListNode* oldHead = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = oldHead;
        }
        return dummy.next;
    }
};
