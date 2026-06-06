// Problem: Same Tree
// Link: https://leetcode.com/problems/same-tree/
// Difficulty: Easy
//
// Approach:
// We recursively check if two binary trees are the same.
// Two trees are the same if they have the same structure and same node values.
//
// - Base case: if both nodes are null, trees are the same.
// - If only one node is null, trees are different.
// - If the node values are different, trees are different.
// - Recursively check if left subtrees are the same.
// - Recursively check if right subtrees are the same.
// - Return true only if all conditions are met.
//
// Time Complexity: O(min(m, n))
//   - m = number of nodes in tree p
//   - n = number of nodes in tree q
//   - We stop as soon as we find a difference
//
// Space Complexity: O(min(h1, h2))
//   - h1 = height of tree p
//   - h2 = height of tree q
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Both nodes are null
        if (p == nullptr && q == nullptr) return true;
        // One node is null, the other is not
        if ((!p && q) || (p && !q)) return false;
        // Node values are different
        if (p->val != q->val) return false;

        // Recursively check left and right subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
