/*
 * LeetCode 21 - Merge Two Sorted Lists
 *
 * Merge two sorted singly-linked lists into a single sorted list by splicing
 * their existing nodes together, and return the head of the merged list.
 *
 * Input  : ListNode* list1, ListNode* list2 (each sorted non-decreasing, possibly empty).
 * Output : head of the merged sorted list.
 * Constraints: 0..50 nodes per list, -100 <= Node.val <= 100.
 *
 * Approach: use a dummy head and a tail pointer. While both lists are non-empty,
 *   splice the node with the smaller value onto the tail (ties take list1, which
 *   keeps the merge stable) and advance that list. When one list is exhausted,
 *   attach the remainder of the other in a single step. Return dummy.next, which
 *   is the real head (this also handles both-empty -> nullptr cleanly).
 *
 * Complexity: O(m + n) time, O(1) extra space (nodes are reused, not copied).
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;                       // simplifies the empty-list edge cases
        ListNode* tail = &dummy;
        while (list1 && list2) {
            if (list1->val <= list2->val) {   // '<=' keeps the merge stable
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        tail->next = list1 ? list1 : list2;   // attach whatever remains (or nullptr)
        return dummy.next;
    }
};
