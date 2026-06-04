// Problem: Merge K Sorted Lists
// Link: https://leetcode.com/problems/merge-k-sorted-lists/
// Difficulty: Hard
//
// Approach:
// We use a divide-and-conquer strategy to merge k sorted lists.
//
// - Recursively divide the list of lists into halves until each half
//   contains only one list.
// - Then merge pairs of lists bottom-up using a two-list merge function.
// - The merge function compares nodes from two lists and builds a merged list.
//
// This approach reduces the problem from merging k lists directly to merging
// many pairs of lists, which is more efficient.
//
// Time Complexity: O(n * log(k))
//   - n = total number of nodes across all lists
//   - k = number of lists
//   - We perform log(k) levels of merging
//
// Space Complexity: O(log(k))
//   - Recursion depth for the divide step

#include <iostream>
#include <vector>

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        return divide(lists, 0, lists.size() - 1);
    }

private:
    ListNode* divide(vector<ListNode*>& lists, int l, int r) {
        if (l > r) {
            return nullptr;
        }

        if (l == r) {
            return lists[l];
        }

        int mid = l + (r - l) / 2;

        ListNode* left = divide(lists, l, mid);
        ListNode* right = divide(lists, mid + 1, r);

        return conquer(left, right);
    }

    ListNode* conquer(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }

        curr->next = l1 ? l1 : l2;

        return dummy.next;
    }
};
