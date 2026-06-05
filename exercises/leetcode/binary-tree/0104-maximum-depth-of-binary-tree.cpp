// Problem: Maximum Depth of Binary Tree
// Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/
// Difficulty: Easy
//
// Approach:
// We recursively find the maximum depth of the binary tree.
//
// - Base case: if the node is null, return 0.
// - Recursively find the maximum depth of the left subtree.
// - Recursively find the maximum depth of the right subtree.
// - Return 1 + the maximum of the two depths.
//
// This approach works from the bottom-up, calculating the depth of each
// subtree and combining them to find the overall maximum depth.
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
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
