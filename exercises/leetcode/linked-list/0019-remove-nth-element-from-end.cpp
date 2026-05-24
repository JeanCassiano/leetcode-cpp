// Problem: Remove Nth Node From End of List
// Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// Difficulty: Medium
//
// Approach:
// We use the two-pointer technique with a dummy node.
//
// - `right` is moved `n` steps ahead.
// - Then both `left` and `right` move together
//   until `right` reaches the end.
// - At that point, `left` points to the node
//   before the one that must be removed.
//
// The dummy node simplifies edge cases,
// such as removing the head node.
//
// Time Complexity: O(n)
//
// Space Complexity: O(1)

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);

        ListNode* left = dummy;
        ListNode* right = head;

        while (n > 0) {
            right = right->next;
            n--;
        }

        while (right != nullptr) {
            left = left->next;
            right = right->next;
        }

        left->next = left->next->next;

        return dummy->next;
    }
};