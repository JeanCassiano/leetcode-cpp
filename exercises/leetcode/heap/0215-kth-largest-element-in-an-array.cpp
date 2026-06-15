// Problem: Kth Largest Element in an Array
// Link: https://leetcode.com/problems/kth-largest-element-in-an-array/
// Difficulty: Medium
//
// Approach:
// We use a min heap to keep track of the k largest elements.
// The top of the min heap is always the kth largest element.
//
// - Add each number to the min heap.
// - If the heap size exceeds k, remove the smallest element.
// - Return the top element (kth largest).
//
// This approach is more efficient than sorting when k is much smaller than n.
//
// Time Complexity: O(n log k)
//   - n = number of elements
//   - Each push and pop operation takes O(log k)
//
// Space Complexity: O(k)
//   - Space used by the min heap

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Add all numbers to the heap, keeping only k largest
        for (auto& num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        // Return the kth largest (top of min heap)
        return minHeap.top();
    }
};
