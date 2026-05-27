// Problem: Reverse Linked List
// Link: https://leetcode.com/problems/reverse-linked-list/
// Difficulty: Easy
//
// Approach:
// We reverse the linked list iteratively using three pointers:
//
// - `prev` stores the previous node.
// - `curr` stores the current node being processed.
// - `next` temporarily stores the next node.
//
// For each node:
//   - Save the next node.
//   - Reverse the current node's pointer.
//   - Move both `prev` and `curr` one step forward.
//
// At the end, `prev` becomes the new head of the reversed list.
//
// Time Complexity: O(n)
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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;
        // here we compare curr and not curr->next, because this would skip the last element
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        // we return prev, given that curr, is a nullptr in this moment

        return prev;
    }
};