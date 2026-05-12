// Problem: Trapping Rain Water
// Link: https://leetcode.com/problems/trapping-rain-water/
// Difficulty: Hard

// Approach:
// We use the two pointers technique combined with a greedy strategy.
// The amount of water trapped at a position depends on:
//
// trapped_water = min(maxLeft, maxRight) - height[i]
//
// Where:
// - maxLeft  = tallest bar seen from the left
// - maxRight = tallest bar seen from the right
//
// Instead of precomputing prefix/suffix arrays,
// we maintain these values dynamically using two pointers:
//
// - left pointer starts at the beginning
// - right pointer starts at the end
//
// At each step:
// - Compare leftMax and rightMax
// - The smaller one determines the maximum water level
//   that can be safely processed
//
// Why?
// Because water trapped at a position is limited by the
// smaller boundary.
//
// If leftMax < rightMax:
// - We move the left pointer
// - Update leftMax
// - Water trapped at left is:
//      leftMax - height[left]
//
// Otherwise:
// - Move the right pointer
// - Update rightMax
// - Water trapped at right is:
//      rightMax - height[right]
//
// This greedy observation allows us to process the array
// in a single pass without extra memory.

// Time Complexity: O(n)
// Space Complexity: O(1)

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()){
            return 0;
        }

        int left = 0, right = height.size() - 1;

        int leftMax = height[left], rightMax = height[right];
        int res = 0;

        while (left < right){
            if (leftMax < rightMax){
                left++;
                leftMax = max(leftMax, height[left]);
                res += leftMax - height[left];
            } else {
                right--;
                rightMax = max(rightMax, height[right]);
                res += rightMax - height[right];
            }
        }

        return res;
    }
};