/*
 * LeetCode 82 - Remove Duplicates from Sorted List II
 *
 * Given the head of a sorted (ascending) singly linked list, delete every node whose
 * value is not unique — that is, remove ALL nodes of any value that appears more than
 * once, keeping only the values that occur exactly once. Return the resulting sorted list.
 *
 * Input  : ListNode* head (sorted ascending, possibly empty).
 * Output : head of the list with all duplicated values entirely removed.
 * Constraints: 0..300 nodes, -100 <= Node.val <= 100, list sorted ascending.
 *
 * Approach: Because the list is sorted, equal values form a contiguous run. Use a dummy
 *   sentinel before the head (so even the first value can be dropped) and two pointers:
 *   prev, the last node confirmed kept, and cur, the run scanner. When cur starts a run of
 *   length >= 2 (cur->next has the same value), skip the entire run and splice it out with
 *   prev->next = cur (the node after the run). When cur's value is unique, keep it by
 *   advancing prev. One pass, relinking only.
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0, head);        // sentinel: lets us drop a run that starts at head
        ListNode* prev = &dummy;        // last node we have decided to keep
        ListNode* cur = head;

        while (cur) {
            if (cur->next && cur->next->val == cur->val) {
                int v = cur->val;                       // this value is duplicated
                while (cur && cur->val == v)            // walk past every node holding it
                    cur = cur->next;
                prev->next = cur;                       // unlink the whole run at once
            } else {
                prev = cur;                             // unique value: keep and advance
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};
