// Problem: Linked List Cycle
// Link: https://leetcode.com/problems/linked-list-cycle/
// Difficulty: Easy
//
// Approach:
// We use Floyd’s Cycle Detection Algorithm
// (also known as the Tortoise and Hare algorithm).
//
// - `slow` moves one step at a time.
// - `fast` moves two steps at a time.
//
// If the linked list contains a cycle,
// the two pointers will eventually meet.
//
// If `fast` reaches nullptr,
// the list does not contain a cycle.
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
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return true;
            }
        }

        return false;
    }
};