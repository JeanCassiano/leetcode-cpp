// Problem: Last Stone Weight
// Link: https://leetcode.com/problems/last-stone-weight/
// Difficulty: Easy
//
// Approach:
// We use a max heap to always get the two heaviest stones.
//
// - Add all stones to a max heap.
// - While there are at least 2 stones:
//   - Remove the two heaviest stones.
//   - If they are different, add the difference back to the heap.
// - Return the last stone weight or 0 if no stones remain.
//
// This greedy approach ensures we always smash the heaviest stones together.
//
// Time Complexity: O(n log n)
//   - n = number of stones
//   - Each push and pop operation takes O(log n)
//
// Space Complexity: O(n)
//   - Space used by the max heap

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int, vector<int>, less<int>> maxHeap;

        // Add all stones to the max heap
        for (int& stone : stones) {
            maxHeap.push(stone);
        }

        // Smash stones until at most one remains
        while (maxHeap.size() > 1) {
            int s1 = maxHeap.top();
            maxHeap.pop();
            int s2 = maxHeap.top();
            maxHeap.pop();

            // If stones have different weights, add the difference back
            if (s1 > s2) {
                s1 = s1 - s2;
                maxHeap.push(s1);
            }
        }

        // Return the last stone or 0 if no stones remain
        if (maxHeap.empty()) {
            return 0;
        } else {
            return maxHeap.top();
        }
    }
};
