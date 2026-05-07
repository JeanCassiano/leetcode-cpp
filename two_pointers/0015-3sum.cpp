// Problem: 3Sum
// Link: https://leetcode.com/problems/3sum/
// Difficulty: Medium

// Approach:
// This problem is an extension of Two Sum II. We first sort the array to enable 
// the two-pointer strategy and easily skip duplicates.
// We iterate through the array, fixing one number (nums[i]) and then searching 
// for the other two numbers (nums[k] and nums[j]) using two pointers.
// - If the sum is < 0, we need a larger value, so we move the left pointer (k++).
// - If the sum is > 0, we need a smaller value, so we move the right pointer (j--).
// - If the sum is 0, we found a triplet.
// To avoid duplicate triplets, we skip identical values for the fixed element 
// and for both pointers after a match is found.

// Time Complexity: O(n^2)
// Space Complexity: O(1) or O(n) (depending on the sorting implementation)

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> output;
        int n = nums.size();
        
        if (n < 3) return output;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            // Skip duplicate values for the first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int k = i + 1;
            int j = n - 1;

            while (k < j) {
                int sum = nums[i] + nums[k] + nums[j];

                if (sum < 0) {
                    k++;
                } else if (sum > 0) {
                    j--;
                } else {
                    output.push_back({nums[i], nums[k], nums[j]});
                    k++;
                    j--;

                    // Skip duplicate values for the second and third elements
                    while (k < j && nums[k] == nums[k - 1]) k++;
                    while (k < j && nums[j] == nums[j + 1]) j--;
                }
            }
        }
        return output;
    }
};