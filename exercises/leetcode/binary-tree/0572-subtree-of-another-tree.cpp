// Problem: Subtree of Another Tree
// Link: https://leetcode.com/problems/subtree-of-another-tree/
// Difficulty: Easy
//
// Approach:
// We check if subRoot is a subtree of root by:
// - Traversing the tree and comparing node values.
// - When we find a matching node value, we check if the entire subtrees match.
// - We use a helper function to check if two trees are identical.
//
// - Base case: if root is null, subRoot cannot be a subtree.
// - If the current node matches and its subtree is the same as subRoot, return true.
// - Recursively check if subRoot is a subtree of the left or right children.
//
// Time Complexity: O(m * n)
//   - m = number of nodes in root
//   - n = number of nodes in subRoot
//   - In worst case, we compare subRoot with every subtree of root
//
// Space Complexity: O(max(h1, h2))
//   - h1 = height of root
//   - h2 = height of subRoot
//   - Space used by the recursion call stack

#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) return false;

        // Check if current subtree matches subRoot
        if (root->val == subRoot->val && isSameTree(root, subRoot)) return true;

        // Recursively check left and right subtrees
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

private:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Both nodes are null
        if (p == nullptr && q == nullptr) return true;
        // One node is null, the other is not
        if ((!p && q) || (p && !q)) return false;
        // Node values are different
        if (p->val != q->val) return false;

        // Recursively check left and right subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
