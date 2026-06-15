// Problem: Kth Largest Element in a Stream
// Link: https://leetcode.com/problems/kth-largest-element-in-a-stream/
// Difficulty: Easy
//
// Approach:
// We use a min heap to keep track of the k largest elements.
// The top of the min heap is always the kth largest element.
//
// Constructor:
// - Add all numbers to the min heap.
// - If the heap size exceeds k, remove the smallest element.
//
// Add:
// - Add the new value to the heap.
// - If the heap size exceeds k, remove the smallest element.
// - Return the top element (kth largest).
//
// Time Complexity:
//   - Constructor: O(n log k) where n = number of elements in nums
//   - Add: O(log k)
//
// Space Complexity: O(k)
//   - Space used by the min heap

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        // Add all numbers to the heap
        for (int num : nums) {
            minHeap.push(num);
            // Keep only the k largest elements
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
    }

    int add(int val) {
        minHeap.push(val);
        // Keep only the k largest elements
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        // Return the kth largest (top of min heap)
        return minHeap.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
