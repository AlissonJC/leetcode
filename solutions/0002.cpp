/*
 * LeetCode 2 - Add Two Numbers
 *
 * Two non-empty linked lists store the digits of two non-negative integers in
 * reverse order (least significant digit first). Add the numbers and return the
 * sum as a linked list in the same reverse-order format.
 *
 * Input  : ListNode* l1, ListNode* l2 (digits in reverse order, no leading zeros).
 * Output : head of the sum list, digits in reverse order.
 * Constraints: 1..100 nodes per list, 0 <= Node.val <= 9.
 *
 * Approach: walk both lists together, lowest digit first. At each step add the
 *   two current digits (0 when a list is exhausted) plus the carry; the new node
 *   stores sum % 10 and the carry becomes sum / 10. Loop while either list has a
 *   node OR a carry remains -- the carry condition emits the final leading digit
 *   (e.g. 99 + 1 = 100). A dummy head keeps the splicing branch-free.
 *
 * Complexity: O(max(m, n)) time, O(max(m, n)) for the output list.
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;
        int carry = 0;
        // Continue while there is a digit left in either list or a pending carry.
        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) { sum += l1->val; l1 = l1->next; }
            if (l2) { sum += l2->val; l2 = l2->next; }
            carry = sum / 10;
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }
        return dummy.next;
    }
};
