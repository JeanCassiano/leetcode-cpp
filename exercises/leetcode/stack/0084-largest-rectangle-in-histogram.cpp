// Problem: Largest Rectangle in Histogram
// Link: https://leetcode.com/problems/largest-rectangle-in-histogram/
// Difficulty: Hard

// Approach:
// We use a monotonic stack to find the nearest smaller element to the left and right for each bar in the histogram.
// Steps:
// 1. For each bar, compute the index of the nearest smaller bar to its left using a stack.
// 2. For each bar, compute the index of the nearest smaller bar to its right using a stack.
// 3. The width of the rectangle for each bar is (rightMost - leftMost + 1), and the area is height * width.
// 4. Track the maximum area among all bars.
// This allows us to compute the largest rectangle efficiently without checking every possible pair of bars.

// Time Complexity: O(n), where n is the number of bars
// Space Complexity: O(n), for the stacks and auxiliary arrays storing left and right boundaries

# include <vector>
# include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> leftMost(n, -1);
        vector<int> rightMost(n, n);
        stack<int> stack;

        for (int i = 0; i < n; i++) {
            while (!stack.empty() && heights[stack.top()] >= heights[i]) {
                stack.pop();
            }
            if (!stack.empty()) {
                leftMost[i] = stack.top();
            }
            stack.push(i);
        }

        while (!stack.empty()) stack.pop();

        for (int i = n - 1; i >= 0; i--) {
            while (!stack.empty() && heights[stack.top()] >= heights[i]) {
                stack.pop();
            }
            if (!stack.empty()) {
                rightMost[i] = stack.top();
            }
            stack.push(i);
        }

        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            leftMost[i] += 1;
            rightMost[i] -= 1;
            maxArea = max(maxArea, heights[i] * (rightMost[i] - leftMost[i] + 1));
        }

        return maxArea;
    }
};