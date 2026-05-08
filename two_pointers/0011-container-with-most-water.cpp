// Problem: Container With Most Water
// Link: https://leetcode.com/problems/container-with-most-water/
// Difficulty: Medium

// Approach:
// We use the two pointers technique combined with a greedy strategy.
// The container area is determined by:
//
// area = min(height[i], height[j]) * (j - i)
//
// We start with the widest possible container:
// - left pointer at the beginning
// - right pointer at the end
//
// At each step:
// - Compute the current area
// - Update the maximum area found
// - Move the pointer with the smaller height
//
// Why move the smaller height?
// Because the smaller side is the limiting factor of the area.
// Moving the taller side would only reduce the width without increasing
// the limiting height, so it cannot produce a better result.
//
// This allows us to eliminate impossible candidates greedily
// while scanning the array only once.

// Time Complexity: O(n)
// Space Complexity: O(1)

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& heights) {
        int i  = 0;
        int j = heights.size() - 1;
        int maximum = 0;

        while (i < j) {
            int distance = j - i;
            int area = min(heights[i], heights[j]) * distance;

            maximum = max(area, maximum);

            if (heights[i] >= heights[j]) {
                j--;
            } else {
                i++;
            }
        }

        return maximum;
    }
};