// Problem: Kth Smallest Element in a BST
// Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
// Difficulty: Medium
//
// Approach:
// We use in-order traversal of a BST to find the kth smallest element.
// In-order traversal visits nodes in ascending order.
//
// - Perform in-order traversal (left -> node -> right).
// - Decrement k for each node visited.
// - When k becomes 0, the current node is the kth smallest.
// - Return the value of that node.
//
// We use a reference to k to maintain its state across recursive calls.
//
// Time Complexity: O(k) in best case, O(n) in worst case
//   - n = number of nodes in the tree
//   - We stop as soon as we find the kth smallest
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
private:
    int inOrder(TreeNode* root, int &k) {
        if (!root) return -1;

        // Traverse left subtree
        int left = inOrder(root->left, k);
        if (left != -1) return left;

        // Process current node
        if (--k == 0) return root->val;

        // Traverse right subtree
        return inOrder(root->right, k);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        return inOrder(root, k);
    }
};
