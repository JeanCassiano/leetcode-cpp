// Problem: Two Sum II - Input Array Is Sorted
// Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
// Difficulty: Medium

// Approach:
// We use a two-pointer technique since the array is sorted.
// One pointer starts at the beginning (i) and the other at the end (j).
// At each step, we compute the sum of both values:
// - If the sum is smaller than the target, we move the left pointer forward (i++).
// - If the sum is larger than the target, we move the right pointer backward (j--).
// - If the sum matches the target, we return the 1-indexed positions.
//
// This works because the sorted property guarantees that moving pointers
// adjusts the sum in a predictable way without needing extra space.

// Time Complexity: O(n)
// Space Complexity: O(1)

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = numbers.size() - 1;

        while (i < j) {
            int sum = numbers[i] + numbers[j];

            if (sum < target) {
                i++;
            } else if (sum > target) {
                j--;
            } else {
                return {i + 1, j + 1};
            }
        }
    }
};