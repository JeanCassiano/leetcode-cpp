// Problem: Binary Tree Maximum Path Sum
// Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/
// Difficulty: Hard
//
// Approach:
// We use DFS to find the maximum path sum in the tree.
// A path can start and end at any node and can go through multiple nodes.
//
// - For each node, calculate the maximum sum from left and right subtrees.
// - If the sum is negative, we can ignore it (use 0).
// - Update the global result with the maximum of current path sum.
// - Return the maximum single path from the current node to either child.
//
// The key insight is that we need to return the maximum path that can be
// extended further (single path), but we track the maximum path sum that
// can pass through the current node (which may not be extendable).
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
    int maxPathSum(TreeNode* root) {
        int res = root->val;
        dfs(root, res);
        return res;
    }

private:
    int dfs(TreeNode* root, int& res) {
        if (!root) {
            return 0;
        }

        // Get maximum sum from left and right, ignore negative sums
        int leftMax = max(dfs(root->left, res), 0);
        int rightMax = max(dfs(root->right, res), 0);

        // Update result with maximum path sum through current node
        res = max(res, root->val + leftMax + rightMax);

        // Return maximum path that can be extended to parent
        return root->val + max(leftMax, rightMax);
    }
};
