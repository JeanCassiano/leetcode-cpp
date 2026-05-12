// Problem: Two Sum
// Link: https://leetcode.com/problems/two-sum/
// Difficulty: Easy

// Approach:
// Use an unordered_map to keep track of the numbers we have seen so far and their indices.
// Iterate through the array, and for each number, calculate its "complement" 
// (the value needed to reach the target: target - current number).
// Use the find() method to check if this complement already exists in our map.
// If it does, we have found our pair and return their indices (complement's index, current index).
// If it doesn't, we add the current number and its index to the map and continue.
// This allows us to find the valid pair in a single pass without double lookups.

// Time Complexity: O(n), where n is the number of elements in the array. We traverse the array exactly once, and map lookups take O(1) time on average.
// Space Complexity: O(n), as the hash map can store up to n elements in the worst-case scenario.

# include <unordered_map>
# include <vector>

using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        int complement;
        for (int i = 0; i < nums.size(); i++){
            complement = target - nums[i];
            auto it = seen.find(complement);
            if (it != seen.end()){
                return {it->second, i};
            }
            seen[nums[i]] = i;
        }
        return {};
    }
};
