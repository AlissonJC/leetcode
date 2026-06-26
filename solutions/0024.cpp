/*
 * LeetCode 24 - Swap Nodes in Pairs
 *
 * Given a singly-linked list, swap every two adjacent nodes and return the new
 * head. The swap must relink the nodes themselves -- the stored values may not be
 * modified. A list of odd length leaves its final lone node untouched.
 *
 * Input  : ListNode* head (0..100 nodes). Output : head of the pairwise-swapped list.
 * Constraints: 0 <= node count <= 100, 0 <= Node.val <= 100.
 *
 * Approach: walk the list with a dummy node placed before the head and a `prev`
 *   pointer that always sits just ahead of the pair being swapped. While two more
 *   nodes exist, relink them into the order prev -> second -> first -> (rest):
 *   point first past second, hang second onto prev, and close the pair by pointing
 *   second back at first. Then advance prev to first, which is now the trailing
 *   node of the swapped pair. The dummy makes returning the new head trivial and
 *   removes any special case for swapping the very first pair. Pure pointer
 *   surgery, so node values are never read or written.
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
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy;                 // sentinel before head; dummy.next is the answer
        dummy.next = head;
        ListNode* prev = &dummy;        // node immediately before the pair to swap

        // A pair needs two real nodes ahead of prev; odd tail just ends the loop.
        while (prev->next && prev->next->next) {
            ListNode* first  = prev->next;        // first node of the pair
            ListNode* second = first->next;       // second node of the pair

            first->next  = second->next;          // first now points past the pair
            second->next = first;                 // second leads, first follows
            prev->next   = second;                // splice the swapped pair back in

            prev = first;                         // first became the pair's new tail
        }
        return dummy.next;
    }
};
