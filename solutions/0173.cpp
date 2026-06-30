/*
 * LeetCode 173 - Binary Search Tree Iterator
 *
 * Implement an iterator over the in-order traversal of a binary search tree. The
 * constructor takes the root and conceptually places the cursor just before the
 * smallest element. next() advances the cursor and returns the value now under it
 * (so the first next() yields the smallest value); hasNext() reports whether any
 * value remains to the right of the cursor. next() is only called when a next value
 * exists.
 *
 * Input  : a sequence of BSTIterator(root), next(), hasNext() operations.
 * Output : next() returns ints in ascending (in-order) order; hasNext() returns bool.
 *
 * Constraints: 1..1e5 nodes; 0 <= Node.val <= 1e6; up to 1e5 calls to next/hasNext.
 *
 * Approach: keep an explicit stack holding the chain of ancestors whose left subtree is
 *   still being processed — i.e. the left spine of the not-yet-visited portion. The
 *   constructor pushes the entire left spine from the root, so the smallest node sits on
 *   top. next() pops that node (the next in-order value) and then pushes the left spine
 *   of its right child, exposing the following in-order node. Every node is pushed and
 *   popped exactly once across all calls, giving amortized O(1) per next(), and the stack
 *   never holds more than the tree height — answering the follow-up's O(h) memory bound.
 *
 * Complexity: next() amortized O(1) (O(n) total over all calls), hasNext() O(1);
 *   O(h) space for the stack, where h is the tree height.
 */

#include <stack>
using namespace std;

// Definition for a binary tree node (provided by LeetCode):
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };

class BSTIterator {
    stack<TreeNode*> st;

    // Push a node and every node down its left spine; the deepest (smallest) ends on top.
    void pushLeftSpine(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode* root) {
        pushLeftSpine(root);                 // cursor sits just before the smallest value
    }

    int next() {
        TreeNode* node = st.top();           // smallest unvisited node
        st.pop();
        pushLeftSpine(node->right);          // expose the next in-order node
        return node->val;
    }

    bool hasNext() {
        return !st.empty();
    }
};
