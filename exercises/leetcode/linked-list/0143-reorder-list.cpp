// Problem: Reorder List
// Link: https://leetcode.com/problems/reorder-list/
// Difficulty: Medium
//
// Approach:
// We use recursion to reorder the linked list.
//
// - `cur` recursively moves to the end of the list.
// - During backtracking, `root` moves forward
//   from the beginning of the list.
// - We connect nodes alternately from the front
//   and the back of the list.
//
// Base cases:
// - If `cur` becomes nullptr, return `root`.
// - If pointers meet or cross,
//   terminate the list by setting `cur->next = nullptr`.
//
// The recursion naturally processes the list
// from the end toward the front.
//
// Time Complexity: O(n)
//
// Space Complexity: O(n)
//   - Recursive call stack

#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        // recursive algorithm to reorder the list
        head = rec(head, head->next);
    }

private:
    ListNode* rec(ListNode* root, ListNode* cur) {

        // in case we finish the list
        if (cur == nullptr) {
            return root;
        }

        // we progress through the list, going until the last element
        // where we have: root = first element, cur = last element
        root = rec(root, cur->next);

        // condition to stop (we already finish and we need to stop the recursion)
        if (root == nullptr) {
            return nullptr;
        }
        // aux node
        ListNode* tmp = nullptr;

        if (root == cur || root->next == cur) {
            cur->next = nullptr;
        } else { // we store the next element of the root, then we make the current element the next of the root, and the old next element, the next element of the cur
            tmp = root->next;
            root->next = cur;
            cur->next = tmp; // this store the next root (where we are going to swap)
        }

        return tmp;
    }
};