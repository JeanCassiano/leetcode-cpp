// Problem: Construct Binary Tree from Preorder and Inorder Traversal
// Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// Difficulty: Medium
//
// Approach:
// We use two pointers (preIdx and inIdx) to traverse preorder and inorder arrays.
// - Preorder: root, left subtree, right subtree
// - Inorder: left subtree, root, right subtree
//
// - The first element in preorder is always the root.
// - Use a limit parameter to know when to stop building a subtree.
// - When we encounter the limit in inorder, we know the subtree is complete.
// - Build left subtree with the current root value as the limit.
// - Build right subtree with the original limit.
//
// This approach avoids searching for the root in inorder, making it more efficient.
//
// Time Complexity: O(n)
//   - n = number of nodes in the tree
//   - Each node is processed once
//
// Space Complexity: O(h)
//   - h = height of the tree
//   - Space used by the recursion call stack

#include <iostream>
#include <vector>
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
    int preIdx = 0;
    int inIdx = 0;

    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int limit) {
        // Base case: reached end of preorder or found the limit in inorder
        if (preIdx >= preorder.size()) return nullptr;
        if (inorder[inIdx] == limit) {
            inIdx++;
            return nullptr;
        }

        // Create node from current preorder element
        TreeNode* root = new TreeNode(preorder[preIdx++]);
        // Build left subtree with current root value as limit
        root->left = dfs(preorder, inorder, root->val);
        // Build right subtree with original limit
        root->right = dfs(preorder, inorder, limit);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return dfs(preorder, inorder, INT_MAX);
    }
};
