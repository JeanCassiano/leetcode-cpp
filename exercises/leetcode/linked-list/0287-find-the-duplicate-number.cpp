// Problem: Find the Duplicate Number
// Link: https://leetcode.com/problems/find-the-duplicate-number/
// Difficulty: Medium
//
// Approach:
// We use Floyd's Cycle Detection algorithm (tortoise and hare).
// Treat the array as a linked list where nums[i] points to index nums[i].
//
// - First phase: Find intersection point in the cycle.
//   * Move slow by 1 step and fast by 2 steps until they meet.
// - Second phase: Find cycle start (the duplicate number).
//   * Reset slow to start and move both by 1 step until they meet.
//   * The meeting point is the duplicate number.
//
// This approach uses O(1) space and doesn't modify the array.
//
// Time Complexity: O(n)
//   - n = length of the array
//
// Space Complexity: O(1)
//   - only using pointers, no extra space

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Phase 1: Find intersection point in the cycle
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Find the start of the cycle (duplicate number)
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};
