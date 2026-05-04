// Problem: Contains Duplicate
// Link: https://leetcode.com/problems/contains-duplicate/
// Difficulty: Easy

// Approach:
// Use an unordered_set to keep track of visited elements.
// The insert() method of std::unordered_set returns a pair.
// The second element of this pair is a boolean that evaluates to false 
// if the element already existed in the set.
// We leverage this to check for duplicates and insert in a single, efficient operation.

// Time Complexity: O(n)
// Space Complexity: O(n)

#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsDuplicate(const std::vector<int>& nums) {
        std::unordered_set<int> seen;

        for (int num : nums) {
            // seen.insert(num) returns a pair: {iterator, bool}
            // The boolean is false if the insertion failed (meaning the element already exists)
            if (!seen.insert(num).second) {
                return true;
            }
        }

        return false;
    }
};