/*
 * LeetCode 707 - Design Linked List
 *
 * Implement a 0-indexed linked list (no built-in list library):
 *   MyLinkedList()                 - create an empty list.
 *   get(int index)                 - value of the index-th node, or -1 if the
 *                                    index is out of range.
 *   addAtHead(int val)             - insert a node at the front.
 *   addAtTail(int val)             - append a node at the back.
 *   addAtIndex(int index, int val) - insert a node before the index-th node;
 *                                    if index == length, append; if index >
 *                                    length, do nothing.
 *   deleteAtIndex(int index)       - remove the index-th node if it exists.
 *
 * Input/Output: a sequence of method calls; get() returns a value or -1.
 *
 * Constraints: 0 <= index, val <= 1000; at most 2000 calls.
 *
 * Approach: a doubly linked list bounded by two sentinel (dummy) nodes, head and
 *   tail, plus a size counter. The sentinels guarantee every real node always has
 *   a non-null predecessor and successor, so every insertion and deletion is the
 *   same handful of pointer rewires with no special-casing of the ends. The size
 *   counter makes index validation O(1), and a lookup walks from whichever end is
 *   nearer to the target index to roughly halve the average traversal.
 *
 * Complexity: get / addAtIndex / deleteAtIndex are O(index) (<= O(n));
 *   addAtHead / addAtTail are O(1); O(n) space for n stored nodes.
 */

class MyLinkedList {
private:
    struct Node {
        int val;
        Node* prev;
        Node* next;
        Node(int v) : val(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;   // sentinel before the first real node
    Node* tail;   // sentinel after the last real node
    int size;

    // Return the real node at 0-indexed position (0 <= index < size), walking in
    // from the closer sentinel.
    Node* nodeAt(int index) {
        Node* cur;
        if (index < size - index) {            // target is in the front half
            cur = head->next;
            for (int i = 0; i < index; ++i) cur = cur->next;
        } else {                                // target is in the back half
            cur = tail->prev;
            for (int i = size - 1; i > index; --i) cur = cur->prev;
        }
        return cur;
    }

    // Splice a new node holding val immediately before `succ`.
    void insertBefore(Node* succ, int val) {
        Node* pred = succ->prev;
        Node* node = new Node(val);
        node->prev = pred;
        node->next = succ;
        pred->next = node;
        succ->prev = node;
        ++size;
    }

public:
    MyLinkedList() {
        head = new Node(0);
        tail = new Node(0);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    ~MyLinkedList() {
        for (Node* cur = head; cur; ) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    int get(int index) {
        if (index < 0 || index >= size) return -1;
        return nodeAt(index)->val;
    }

    void addAtHead(int val) { insertBefore(head->next, val); }

    void addAtTail(int val) { insertBefore(tail, val); }

    void addAtIndex(int index, int val) {
        if (index > size) return;              // beyond the end: ignore
        if (index < 0) index = 0;              // clamp (constraints keep index >= 0)
        // Insert before the index-th node, or before the tail sentinel to append.
        Node* succ = (index == size) ? tail : nodeAt(index);
        insertBefore(succ, val);
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        Node* node = nodeAt(index);
        node->prev->next = node->next;         // unlink from both neighbours
        node->next->prev = node->prev;
        delete node;
        --size;
    }
};
