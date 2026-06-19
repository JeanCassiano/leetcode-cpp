// Problem: Subsets
// Link: https://leetcode.com/problems/subsets/
// Difficulty: Medium
//
// Approach:
// We use backtracking (DFS) to generate all possible subsets.
//
// The idea is to make decisions for each element:
// - Include the element in the current subset
// - Exclude the element from the current subset
//
// DFS:
// - Base case: when index reaches the end of nums, add the current subset
// - Recursive case:
//   1. Include nums[i]: add it to subset and recurse
//   2. Exclude nums[i]: remove it from subset and recurse
//
// Time Complexity: O(n * 2^n)
//   - There are 2^n subsets
//   - Each subset takes O(n) time to copy into the result
//
// Space Complexity: O(2^n)
//   - Storage for all subsets

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> subset;

        dfs(nums, 0, subset, res);
        return res;
    }

private:
    void dfs(const vector<int>& nums, int i, vector<int>& subset, vector<vector<int>>& res) {
        // Base case: reached the end
        if (i >= nums.size()) {
            res.push_back(subset);
            return;
        }

        // Include nums[i]
        subset.push_back(nums[i]);
        dfs(nums, i + 1, subset, res);

        // Exclude nums[i]
        subset.pop_back();
        dfs(nums, i + 1, subset, res);
    }
};
