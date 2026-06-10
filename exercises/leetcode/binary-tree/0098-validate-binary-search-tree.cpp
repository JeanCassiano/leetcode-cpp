// Problem: Validate Binary Search Tree
// Link: https://leetcode.com/problems/validate-binary-search-tree/
// Difficulty: Medium
//
// Approach:
// We use DFS to validate that the tree is a valid BST.
// For a valid BST, every node must satisfy:
// - Its value is greater than all values in its left subtree.
// - Its value is less than all values in its right subtree.
//
// - We maintain min and max bounds for each node.
// - Initially, min = INT_MIN and max = INT_MAX.
// - For the left child, the max becomes the current node's value.
// - For the right child, the min becomes the current node's value.
// - If any node violates these bounds, return false.
//
// Time Complexity: O(n)
//   - n = number of nodes in the tree
//   - Each node is visited once
//
// Space Complexity: O(h)
//   - h = height of the tree
//   - Space used by the recursion call stack

#include <iostream>
#include <climits>

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
private:
    bool dfs(TreeNode* node, long min, long max) {
        if (!node) return true;

        // Check if current node violates BST property
        if (node->val <= min || node->val >= max) return false;

        // Recursively validate left and right subtrees with updated bounds
        return dfs(node->left, min, node->val) && dfs(node->right, node->val, max);
    }

public:
    bool isValidBST(TreeNode* root) {
        return dfs(root, LLONG_MIN, LLONG_MAX);
    }
};
