// Problem: Maximum Average Subarray I
// Link: https://leetcode.com/problems/maximum-average-subarray-i
// Difficulty: Easy

// Approach:
// We use a sliding window strategy to efficiently find the subarray of length k
// with the maximum average.
//
// The main idea is:
//
// - First, calculate the sum of the first k elements (initial window).
// - Then, slide the window one element at a time:
//   - Subtract the element leaving the window
//   - Add the new element entering the window
//   - Keep track of the maximum sum seen so far
//
// Finally, divide the maximum sum by k to get the maximum average.
//
// Time Complexity: O(n) - we traverse the array once
// Space Complexity: O(1) - we use only a few variables

#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        int l = 0;
        for (int i = 0; i < k; i++){
            sum += nums[i];
        }
        int res = sum;
        for (int r = k; r < nums.size(); r++){
            sum = sum - nums[l] + nums[r];
            res = max(sum, res);
            l++;
        }

        return (double(res)/k);
    }
};