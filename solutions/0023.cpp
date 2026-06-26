/*
 * LeetCode 23 - Merge k Sorted Lists
 *
 * Given k singly-linked lists, each already sorted in ascending order, merge them
 * all into one sorted linked list and return its head. Existing nodes are spliced
 * together rather than copied.
 *
 * Input  : vector<ListNode*> lists -- k lists, any of them possibly empty, and the
 *          vector itself may be empty. Output : head of the single merged list.
 * Constraints: 0 <= k <= 1e4, 0 <= lists[i].length <= 500,
 *              -1e4 <= node value <= 1e4, sum of all lengths <= 1e4.
 *
 * Approach: keep a min-heap holding the current front node of every still-nonempty
 *   list, ordered by node value. Repeatedly pop the global minimum, splice it onto
 *   the result's tail, and push that node's successor (if any) back into the heap.
 *   The heap never holds more than k nodes, so each of the N total nodes is pushed
 *   and popped exactly once at O(log k) apiece. A dummy head absorbs the empty
 *   cases (no lists at all, or every list empty) with no special-casing. An
 *   alternative with the same O(N log k) bound is divide-and-conquer pairwise
 *   merging; the heap is chosen here for its single, self-contained pass.
 *
 * Complexity: O(N log k) time where N is the total number of nodes; O(k) extra
 *   space for the heap.
 */

#include <vector>
#include <queue>
using namespace std;

// Definition for singly-linked list (provided by LeetCode):
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
private:
    // Order pointers by value with '>' so the SMALLEST value sits on top, turning
    // priority_queue's default max-heap into the min-heap we need.
    struct Compare {
        bool operator()(const ListNode* a, const ListNode* b) const {
            return a->val > b->val;
        }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> heap;

        // Seed the heap with every list's head, skipping the empty lists.
        for (ListNode* head : lists)
            if (head) heap.push(head);

        ListNode dummy;                 // sentinel: empty input falls through to nullptr
        ListNode* tail = &dummy;
        while (!heap.empty()) {
            ListNode* node = heap.top();    // global minimum across all list fronts
            heap.pop();
            tail->next = node;              // splice the minimum onto the result
            tail = node;
            if (node->next)                 // that list's next node is a new front
                heap.push(node->next);
        }
        tail->next = nullptr;           // terminate the merged list explicitly
        return dummy.next;              // dummy.next is the real head (nullptr if none)
    }
};
