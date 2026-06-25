/*
 * LeetCode 83 - Remove Duplicates from Sorted List
 *
 * Given the head of a sorted linked list, delete duplicate nodes so each value
 * appears only once, and return the (still sorted) list.
 *
 * Input  : ListNode* head (sorted ascending, possibly empty).
 * Output : head of the de-duplicated list.
 * Constraints: 0..300 nodes, -100 <= Node.val <= 100.
 *
 * Approach: because the list is sorted, equal values are adjacent. Walk with a
 *   single pointer cur: whenever the next node holds the same value, splice it
 *   out (cur->next = cur->next->next) and stay on cur to check the new next;
 *   otherwise advance cur. The head never changes, so just return it.
 *
 * Complexity: O(n) time, O(1) extra space (nodes are relinked, not copied).
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
        ListNode* cur = head;
        while (cur && cur->next) {
            if (cur->next->val == cur->val) {
                cur->next = cur->next->next;   // drop the duplicate, recheck new next
            } else {
                cur = cur->next;               // distinct value: move on
            }
        }
        return head;
    }
};
