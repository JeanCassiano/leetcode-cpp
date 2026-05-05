// Problem: Product of Array Except Self
// Link: https://leetcode.com/problems/product-of-array-except-self/
// Difficulty: Medium

// Approach:
// This problem is solved using a prefix and suffix product strategy without using division.
//
// We want each index i to contain the product of all elements in the array except nums[i].
// Instead of computing this directly (which would be O(n^2)), we break it into two parts:
//
// 1. Prefix pass (left to right):
//    result[i] stores the product of all elements to the left of index i.
//    We build this incrementally using previously computed results.
//
// 2. Suffix pass (right to left):
//    We maintain a running product called `right`, which stores the product of all elements to the right of index i.
//    As we move from right to left, we update `right` and multiply it into result[i].
//
// This way, each position i becomes:
//    result[i] = (product of left side) * (product of right side)
//
// Time Complexity: O(n), where n is the size of nums. We traverse the array twice.
// Space Complexity: O(1) extra space (excluding output array), since we reuse the result array and a single variable.

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(), 1);

        // Prefix pass: build left products
        for (int i = 1; i < nums.size(); i++) {
            result[i] = result[i - 1] * nums[i - 1];
        }

        // Suffix pass: multiply right products
        int right = 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            right *= nums[i + 1];
            result[i] *= right;
        }

        return result;
    }
};