// Problem: Balanced Binary Tree
// Link: https://leetcode.com/problems/balanced-binary-tree/
// Difficulty: Easy
//
// Approach:
// We use DFS to check if the binary tree is balanced.
// A balanced tree is one where the height difference between left and right
// subtrees is at most 1 for every node.
//
// - For each node, we calculate the height of its left and right subtrees.
// - If either subtree is unbalanced, we return -1.
// - If the height difference is greater than 1, we return -1.
// - Otherwise, we return the height of the current subtree.
// - A height of -1 indicates the tree is unbalanced.
//
// Time Complexity: O(n)
//   - n = number of nodes in the tree
//   - Each node is visited once
//
// Space Complexity: O(h)
//   - h = height of the tree
//   - Space used by the recursion call stack

#include <iostream>
#include <algorithm>
#include <cstdlib>

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
    bool isBalanced(TreeNode* root) {
        return dfs(root) != -1;
    }

private:
    int dfs(TreeNode* root) {
        if (!root) {
            return 0;
        }

        // Get heights of left and right subtrees
        int left = dfs(root->left);
        int right = dfs(root->right);

        // If either subtree is unbalanced, return -1
        if (left == -1 || right == -1) return -1;
        // If height difference is greater than 1, tree is unbalanced
        if (abs(left - right) > 1) return -1;

        // Return height of current subtree
        return 1 + max(left, right);
    }
};
