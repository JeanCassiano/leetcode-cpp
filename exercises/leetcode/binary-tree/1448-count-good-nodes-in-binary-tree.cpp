// Problem: Count Good Nodes in Binary Tree
// Link: https://leetcode.com/problems/count-good-nodes-in-binary-tree/
// Difficulty: Medium
//
// Approach:
// A "good" node is one whose value is greater than or equal to all values
// on the path from root to that node.
//
// - We perform a DFS traversal keeping track of the maximum value seen so far.
// - If the current node's value is greater than or equal to the max, it's a good node.
// - Update the max and increment the count.
// - Recursively check the left and right subtrees with the updated max.
// - Return the total count of good nodes.
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
    int goodNodes(TreeNode* root) {
        return rec(root, root->val);
    }

private:
    int rec(TreeNode* root, int higher) {
        int res = 0;

        // If current node is greater than or equal to the max on the path, it's a good node
        if (root->val >= higher) {
            higher = root->val;
            res++;
        }

        // Recursively check left and right subtrees
        if (root->left) res += rec(root->left, higher);
        if (root->right) res += rec(root->right, higher);

        return res;
    }
};
