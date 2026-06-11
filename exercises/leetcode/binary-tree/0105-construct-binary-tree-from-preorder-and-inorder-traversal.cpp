// Problem: Construct Binary Tree from Preorder and Inorder Traversal
// Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// Difficulty: Medium
//
// Approach:
// We use the properties of preorder and inorder traversals to reconstruct the tree.
// - Preorder: root, left subtree, right subtree
// - Inorder: left subtree, root, right subtree
//
// - The first element in preorder is always the root.
// - Find the root in inorder to divide left and right subtrees.
// - Calculate the size of the left subtree.
// - Recursively build left subtree using the next preStart + 1.
// - Recursively build right subtree using preStart + leftSize + 1.
//
// Time Complexity: O(n^2)
//   - n = number of nodes in the tree
//   - Finding the root position in inorder takes O(n) for each node
//
// Space Complexity: O(h)
//   - h = height of the tree
//   - Space used by the recursion call stack

#include <iostream>
#include <vector>

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode* build(vector<int>& pre, int preStart,
                    vector<int>& in, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;

        // The first element in preorder is the root
        TreeNode* root = new TreeNode(pre[preStart]);

        // Find the root position in inorder
        int mid = 0;
        for (int i = inStart; i <= inEnd; i++) {
            if (in[i] == root->val) {
                mid = i;
                break;
            }
        }

        // Calculate the size of the left subtree
        int leftSize = mid - inStart;

        // Recursively build left and right subtrees
        root->left = build(pre, preStart + 1, in, inStart, mid - 1);
        root->right = build(pre, preStart + leftSize + 1, in, mid + 1, inEnd);

        return root;
    }
};
