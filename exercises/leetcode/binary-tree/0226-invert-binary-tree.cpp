// Problem: Invert Binary Tree
// Link: https://leetcode.com/problems/invert-binary-tree/
// Difficulty: Easy
//
// Approach:
// We recursively invert the binary tree by swapping the left and right children
// of each node.
//
// - Recursively invert the left subtree.
// - Recursively invert the right subtree.
// - Swap the left and right children of the current node.
// - Return the root.
//
// This approach is simple and elegant, working from the bottom-up to ensure
// all subtrees are inverted before swapping at each level.
//
// Time Complexity: O(n)
//   - n = number of nodes in the tree
//   - Each node is visited once
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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        // Recursively invert left and right subtrees
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        // Swap left and right children
        root->left = right;
        root->right = left;

        return root;
    }
};
