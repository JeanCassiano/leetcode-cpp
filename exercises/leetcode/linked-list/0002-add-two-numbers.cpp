// Problem: Add Two Numbers
// Link: https://leetcode.com/problems/add-two-numbers/
// Difficulty: Medium
//
// Approach:
// We simulate digit-by-digit addition using a dummy node.
//
// - Traverse both lists simultaneously.
// - At each step, sum the current digits plus any carry.
// - Create a new node with (sum % 10) and update carry = sum / 10.
// - Continue until both lists are exhausted and carry is zero.
//
// The dummy node simplifies handling the head of the result list.
//
// Time Complexity: O(max(n, m))
//   - n = number of nodes in l1
//   - m = number of nodes in l2
//
// Space Complexity: O(max(n, m))
//   - for the output linked list

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        int carry = 0;

        while (l1 || l2 || carry) {
            int sum = carry;

            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;

            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }

        return dummy.next;
    }
};
