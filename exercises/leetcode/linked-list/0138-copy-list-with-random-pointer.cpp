// Problem: Copy List with Random Pointer
// Link: https://leetcode.com/problems/copy-list-with-random-pointer/
// Difficulty: Medium
//
// Approach: In-place interweaving with three passes (O(1) extra space)
//
// Instead of using a hash map to track original→copy mappings, we temporarily
// hijack the `random` pointer of each original node to store its copy, and the
// `next` pointer of each copy to store the original's random target. This lets
// us resolve all pointers with three linear passes and no auxiliary storage.
//
// Pass 1 — Create copies and embed them into the original list:
//   For each original node l1, create a copy l2.
//   - Store the original random target in l2->next  (so we don't lose it).
//   - Overwrite l1->random with l2  (use it as a direct pointer to the copy).
//
//   After this pass: original->random == its own copy,
//                    copy->next       == original's random target.
//
// Pass 2 — Wire up each copy's random pointer:
//   For each original node l1, its copy l2 = l1->random.
//   The original random target is still in l2->next.
//   If that target exists, its copy is target->random (set in Pass 1).
//   So: l2->random = (l2->next != nullptr) ? l2->next->random : nullptr.
//
// Pass 3 — Restore the original list and set each copy's next pointer:
//   For each original node l1, its copy l2 = l1->random.
//   - Restore l1->random = l2->next  (the original random target saved in Pass 1).
//   - Set     l2->next   = (l1->next != nullptr) ? l1->next->random : nullptr
//             (the copy of the next original node, which was stored in Pass 1).
//
// Time Complexity:  O(n)  — three sequential passes over the list.
// Space Complexity: O(1)  — no extra data structures; the output list is not counted.


class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        // Pass 1: for every original node l1, create its copy l2.
        // Save original random in l2->next; point l1->random at l2.
        Node* l1 = head;
        while (l1) {
            Node* l2 = new Node(l1->val);
            l2->next = l1->random;   // preserve original random target
            l1->random = l2;         // hijack random to point at the copy
            l1 = l1->next;
        }

        Node* newHead = head->random; // copy of the original head

        // Pass 2: set each copy's random pointer.
        // l2->next holds the original random target; if it exists, its copy
        // is already stored in that target's random field (from Pass 1).
        l1 = head;
        while (l1) {
            Node* l2 = l1->random;
            l2->random = (l2->next != nullptr) ? l2->next->random : nullptr;
            l1 = l1->next;
        }

        // Pass 3: restore original random pointers and wire copy->next.
        l1 = head;
        while (l1) {
            Node* l2 = l1->random;
            l1->random = l2->next;   // restore: original random was in l2->next
            l2->next = (l1->next != nullptr) ? l1->next->random : nullptr;
            l1 = l1->next;
        }

        return newHead;
    }
};
