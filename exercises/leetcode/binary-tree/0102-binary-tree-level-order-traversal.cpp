// Problem: Binary Tree Level Order Traversal
// Link: https://leetcode.com/problems/binary-tree-level-order-traversal/
// Difficulty: Medium
//
// Approach:
// We use a queue (BFS) to traverse the tree level by level.
//
// - Initialize a queue with the root node.
// - While the queue is not empty:
//   - Get the current level size (number of nodes at this level).
//   - For each node at the current level:
//     - Dequeue the node and add its value to the current level vector.
//     - Enqueue its left and right children (if they exist).
//   - Add the current level vector to the result.
//
// Time Complexity: O(n)
//   - n = number of nodes in the tree
//   - Each node is visited once
//
// Space Complexity: O(w)
//   - w = maximum width of the tree (maximum number of nodes at any level)
//   - Space used by the queue

#include <iostream>
#include <vector>
#include <queue>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;

            // Process all nodes at the current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);

                // Enqueue children
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            res.push_back(level);
        }
        return res;
    }
};
