// Problem: Sliding Window Maximum
// Link: https://leetcode.com/problems/sliding-window-maximum/description/
// Difficulty: Hard

// We use a deque to maintain indices of elements in the current window
// The deque always keeps elements in decreasing order of value
// The front of the deque is the index of the maximum element in the current window
// We slide the window using left (l) and right (r) pointers
// When the window reaches size k, we record the maximum and move the left pointer

// Time Complexity: O(n), each element is pushed and popped at most once
// Space Complexity: O(k), for storing indices in the deque

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> output; // Result vector
        deque<int> q;       // Deque to store indices of elements

        int l = 0; // Left pointer of the window
        for (int r = 0; r < nums.size(); r++){ // Right pointer iterates over all elements
            int windowSize = r - l + 1;

            // Remove indices whose corresponding values are less than nums[r]
            while (!q.empty() && nums[q.back()] < nums[r]){
                q.pop_back();
            }

            // Add current index to the deque
            q.push_back(r);

            // Remove indices that are outside the current window
            if (q.front() < l){
                q.pop_front();
            }

            // If window has reached size k, record the max and slide the window
            if (windowSize == k){
                output.push_back(nums[q.front()]); // Front of deque is the max
                l++; // Move left pointer to shrink the window
            }
        }

        return output;
    }
};