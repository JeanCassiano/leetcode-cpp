// Problem: Serialize and Deserialize Binary Tree
// Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
// Difficulty: Hard
//
// Approach:
// We use level-order traversal (BFS) to serialize and deserialize the tree.
//
// Serialize:
// - Perform BFS and append each node's value (or "N" for null) to a string.
// - Separate values with commas.
//
// Deserialize:
// - Parse the serialized string by splitting on commas.
// - Build the tree level by level using a queue.
// - For each parent node, create left and right children.
//
// Time Complexity: O(n)
//   - n = number of nodes in the tree
//   - Both serialization and deserialization visit each node once
//
// Space Complexity: O(w)
//   - w = maximum width of the tree (maximum number of nodes at any level)
//   - Space used by the queue

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

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

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "N";

        string res;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (!node) {
                res += "N,";
            } else {
                res += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        string val;

        getline(ss, val, ',');
        if (val == "N") return nullptr;

        TreeNode* root = new TreeNode(stoi(val));
        queue<TreeNode*> q;
        q.push(root);

        while (getline(ss, val, ',')) {
            TreeNode* node = q.front();
            q.pop();

            // Process left child
            if (val != "N") {
                node->left = new TreeNode(stoi(val));
                q.push(node->left);
            }

            // Process right child
            getline(ss, val, ',');
            if (val != "N") {
                node->right = new TreeNode(stoi(val));
                q.push(node->right);
            }
        }
        return root;
    }
};
