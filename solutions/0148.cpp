/*
 * LeetCode 148 - Sort List
 *
 * Sort a singly linked list in ascending order by value and return the new head.
 *
 * Input  : the head of a singly linked list.
 * Output : the head of the same nodes re-linked into non-decreasing order.
 *
 * Constraints: 0 <= number of nodes <= 5e4; -1e5 <= Node.val <= 1e5. Follow-up asks for
 *   O(n log n) time and O(1) auxiliary space.
 *
 * Approach: bottom-up (iterative) merge sort, which meets the O(1)-space follow-up that a
 *   recursive top-down split cannot (recursion costs O(log n) stack). Treat the list as
 *   already broken into sorted runs of length 1, then repeatedly double the run length:
 *   for size = 1, 2, 4, ..., sweep the list taking two consecutive runs of `size` nodes,
 *   merging them into the output, and stitching the result onto a running tail via a dummy
 *   head. After the pass for a given size, every block of 2*size nodes is sorted; after
 *   ceil(log2 n) passes the whole list is sorted. Only a handful of pointers are used, so
 *   the extra space is constant.
 *
 * Complexity: O(n log n) time (log n passes, each merging all n nodes once), O(1) extra
 *   space.
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
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next)
            return head;                       // 0 or 1 node: already sorted

        // Count nodes so we know when the run size covers the whole list.
        int n = 0;
        for (ListNode* p = head; p; p = p->next)
            ++n;

        ListNode dummy(0);
        dummy.next = head;

        // Merge runs of length 1, 2, 4, ... until one run spans everything.
        for (int size = 1; size < n; size <<= 1) {
            ListNode* tail = &dummy;           // end of the portion merged so far this pass
            ListNode* cur = dummy.next;        // next node awaiting processing
            while (cur) {
                ListNode* left = cur;                 // first run starts here
                ListNode* right = split(left, size);  // cut left to `size`; right = second run
                cur = split(right, size);             // cut right to `size`; cur = following pair
                tail = merge(left, right, tail);      // merge the pair onto the output tail
            }
        }
        return dummy.next;
    }

private:
    // Advance `size` nodes from head, sever the link, and return the head of the remainder
    // (nullptr if the list ran out first).
    ListNode* split(ListNode* head, int size) {
        for (int i = 1; head && i < size; ++i)
            head = head->next;
        if (!head)
            return nullptr;
        ListNode* rest = head->next;
        head->next = nullptr;                  // terminate this run
        return rest;
    }

    // Merge sorted lists l1 and l2, appending onto `tail`; return the tail of the result.
    ListNode* merge(ListNode* l1, ListNode* l2, ListNode* tail) {
        ListNode* cur = tail;
        while (l1 && l2) {
            if (l1->val <= l2->val) {          // <= keeps the sort stable
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;              // attach whatever remains
        while (cur->next)                      // walk to the actual last node
            cur = cur->next;
        return cur;
    }
};
