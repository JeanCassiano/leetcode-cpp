// Problem: Reverse Nodes in K-Group
// Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
// Difficulty: Hard
//
// Approach:
// We reverse every k consecutive nodes in the linked list.
//
// - First, check if there are at least k nodes remaining.
// - If yes, reverse the current group of k nodes.
// - Connect the tail of the previous group to the head of the reversed group.
// - Move to the next group and repeat until fewer than k nodes remain.
//
// We use a dummy node to simplify handling the head of the list and
// a helper function to reverse a group of k nodes.
//
// Time Complexity: O(n)
//   - n = number of nodes in the list
//   - Each node is visited a constant number of times
//
// Space Complexity: O(1)
//   - Only using pointers, no extra data structures

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (true) {
            // Check if there are at least k nodes remaining
            ListNode* check = head;
            int count = 0;
            while (check != nullptr && count < k) {
                check = check->next;
                count++;
            }
            if (count < k) break;

            ListNode* groupHead = head;
            ListNode* nextGroup = nullptr;
            ListNode* newHead = reverse(head, k, nextGroup);

            // Connect previous group tail to current reversed group head
            tail->next = newHead;
            // Move tail to the end of the reversed group (which is groupHead after reversal)
            tail = groupHead;
            // Connect to the next group
            tail->next = nextGroup;
            // Move to the next group
            head = nextGroup;
        }
        tail->next = head;
        return dummy.next;
    }

private:
    ListNode* reverse(ListNode* head, int k, ListNode*& nextGroup) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr && k > 0) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            k--;
        }
        nextGroup = curr;
        return prev;
    }
};
