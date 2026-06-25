/*
 * LeetCode 94 - Binary Tree Inorder Traversal
 *
 * Return the inorder traversal (left subtree, node, right subtree) of a binary
 * tree's node values.
 *
 * Input  : TreeNode* root (possibly null).
 * Output : vector<int> of the values in inorder.
 * Constraints: 0..100 nodes, -100 <= Node.val <= 100.
 *
 * Approach: iterative inorder with an explicit stack (answers the follow-up).
 *   From the current node, walk left as far as possible, pushing each node;
 *   that puts the deepest-left node on top. Pop it, record its value, then move
 *   to its right child and repeat. A node is visited only after its entire left
 *   subtree, which is exactly inorder order.
 *
 * Complexity: O(n) time, O(h) space for the stack (h = tree height).
 */

#include <vector>
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

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur || !st.empty()) {
            while (cur) {                  // dive to the leftmost unvisited node
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            result.push_back(cur->val);    // left subtree done -> visit this node
            cur = cur->right;              // then process the right subtree
        }
        return result;
    }
};
