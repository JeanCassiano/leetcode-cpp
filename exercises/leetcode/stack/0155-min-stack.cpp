// Problem: Min Stack
// Link: https://leetcode.com/problems/min-stack/
// Difficulty: Medium

// Approach:
// We implement a stack that supports retrieving the minimum element in constant time.
// Each node stores:
// - val: the value of the element
// - min_so_far: the minimum value in the stack up to this node
// - next: pointer to the next node
// When pushing a new value, we update min_so_far as the minimum of the new value and the current stack minimum.
// Pop simply removes the top node, top returns its value, and getMin returns the min_so_far of the top node.

// Time Complexity: O(1) for push, pop, top, and getMin operations
// Space Complexity: O(n), where n is the number of elements in the stack

# include <algorithm>
using namespace std;
class MinStack {
private:
    struct Node {
        int val;
        int min_so_far;
        Node* next;
    };
    Node* head = nullptr;

public:
    MinStack() {
    }
    
    void push(int val) {
        Node* new_node = new Node{val, val, head};
        if (head != nullptr) {
            new_node->min_so_far = min(val, head->min_so_far);
        }
        head = new_node;
    }
    
    void pop() {
        if (head != nullptr) {
            Node* to_delete = head;
            head = head->next;
            delete to_delete;
        }
    }
    
    int top() {
        if (head != nullptr){
            return head->val;
        }
    }
    
    int getMin() {
        return head->min_so_far;
    }
};
