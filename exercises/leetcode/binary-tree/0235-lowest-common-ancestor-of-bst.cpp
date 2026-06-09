// Problem: Lowest Common Ancestor of a Binary Search Tree
// Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// Difficulty: Easy
//
// Approach:
// We use the properties of a Binary Search Tree (BST) to find the LCA.
// In a BST, all values in the left subtree are smaller than the root,
// and all values in the right subtree are larger than the root.
//
// - If both p and q are smaller than root, LCA is in the left subtree.
// - If both p and q are larger than root, LCA is in the right subtree.
// - Otherwise, the current root is the LCA.
//
// This approach exploits the BST property to avoid unnecessary traversals.
//
// Time Complexity: O(h)
//   - h = height of the tree
//   - In worst case (skewed tree), O(n)
//
// Space Complexity: O(h)
//   - h = height of the tree
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Both p and q are in the left subtree
        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        // Both p and q are in the right subtree
        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        // p and q are on different sides, or one of them is root
        return root;
    }
};
