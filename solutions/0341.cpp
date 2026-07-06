/*
 * LeetCode 341 - Flatten Nested List Iterator
 *
 * You are given a nested list of integers. Each element is either a plain integer
 * or a list whose own elements are again integers or nested lists, to any depth.
 * Implement an iterator that yields every integer in left-to-right, depth-first
 * order, as if the whole structure had been flattened.
 *
 * Input  : a sequence of NestedIterator(nestedList), next(), hasNext() operations.
 *          next() is only called after hasNext() has returned true.
 * Output : next() returns the integers of the flattened list in order; hasNext()
 *          returns whether any integer remains.
 *
 * Constraints: 1 <= nestedList.length <= 500; each integer is in [-1e6, 1e6];
 *   nesting can be arbitrarily deep within those elements.
 *
 * Approach: flatten lazily with an explicit stack instead of pre-expanding the whole
 *   structure in the constructor. The stack holds pointers to the not-yet-visited
 *   NestedInteger nodes, with the next one to inspect on top. To make the leftmost
 *   element come out first, a list's children are pushed in reverse order. hasNext()
 *   does the real work: while the top is a list it pops that container and pushes its
 *   children (reversed), repeating until an integer surfaces on top or the stack drains.
 *   next() then just reads and pops that exposed integer. Because every node is pushed
 *   and popped exactly once over the whole iteration, the amortized cost per call is
 *   O(1). We store pointers rather than copies: the caller keeps nestedList (and all the
 *   vectors nested inside it) alive for the iterator's lifetime, so those addresses stay
 *   valid and we avoid deep-copying nested lists.
 *
 * Complexity: next()/hasNext() amortized O(1) (O(N) total over all calls, N = number of
 *   NestedInteger nodes); O(N) worst-case space for the stack.
 */

#include <stack>
#include <vector>
using namespace std;

// This is the interface that allows for creating nested lists (provided by LeetCode).
// You should not implement it, or speculate about its implementation:
// class NestedInteger {
//   public:
//     // Return true if this NestedInteger holds a single integer, rather than a nested list.
//     bool isInteger() const;
//
//     // Return the single integer that this NestedInteger holds, if it holds a single integer.
//     // The result is undefined if this NestedInteger holds a nested list.
//     int getInteger() const;
//
//     // Return the nested list that this NestedInteger holds, if it holds a nested list.
//     // The result is undefined if this NestedInteger holds a single integer.
//     const vector<NestedInteger> &getList() const;
// };

class NestedIterator {
    // Pointers into the original structure; the top is the next node to inspect.
    stack<const NestedInteger*> pending;

    // Push a list's elements so that its FIRST element ends up on top of the stack
    // (push right-to-left). This preserves left-to-right output order.
    void pushReversed(const vector<NestedInteger>& list) {
        for (int i = (int)list.size() - 1; i >= 0; --i)
            pending.push(&list[i]);
    }

public:
    NestedIterator(vector<NestedInteger>& nestedList) {
        pushReversed(nestedList);            // seed with the top-level list, first element on top
    }

    int next() {
        // hasNext() has already exposed an integer on top, so just consume it.
        int value = pending.top()->getInteger();
        pending.pop();
        return value;
    }

    bool hasNext() {
        // Expand lists lazily until an integer is exposed on top, or nothing remains.
        while (!pending.empty()) {
            const NestedInteger* top = pending.top();
            if (top->isInteger())
                return true;                 // an integer is ready for next() to return
            pending.pop();                   // top is a list container: remove it...
            pushReversed(top->getList());    // ...and replace it with its children
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
