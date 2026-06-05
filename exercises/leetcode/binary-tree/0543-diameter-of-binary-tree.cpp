// Problem: Diameter of Binary Tree
// Link: https://leetcode.com/problems/diameter-of-binary-tree/
// Difficulty: Easy
//
// Approach:
// We use DFS to find the diameter of the binary tree.
// The diameter is the longest path between any two nodes in the tree.
//
// - For each node, we calculate the height of its left and right subtrees.
// - The diameter at each node is the sum of its left and right heights.
// - We keep track of the maximum diameter found.
// - The DFS function returns the height of the subtree rooted at the current node.
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
    int diameterOfBinaryTree(TreeNode* root) {
        int result = 0;
        dfs(root, result);
        return result;
    }

private:
    int dfs(TreeNode* root, int& result) {
        if (!root) return 0;

        // Get height of left and right subtrees
        int left = dfs(root->left, result);
        int right = dfs(root->right, result);

        // Update result with the diameter at current node
        result = max(result, left + right);

        // Return height of current subtree
        return 1 + max(left, right);
    }
};
