// Problem: Merge Two Sorted Lists
// Link: https://leetcode.com/problems/merge-two-sorted-lists/
// Difficulty: Easy
//
// Approach:
// We use a dummy node to simplify the merging process.
//
// - Compare the current nodes of both linked lists.
// - Attach the smaller node to the merged list.
// - Move the corresponding pointer forward.
// - Continue until one list becomes empty.
// - Attach the remaining nodes from the non-empty list.
//
// The dummy node helps avoid handling special cases
// for the head of the merged list.
//
// Time Complexity: O(n + m)
//   - n = number of nodes in list1
//   - m = number of nodes in list2
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        tail->next = (list1 != nullptr) ? list1 : list2;

        return dummy.next;
    }
};