// Problem: Binary Search
// Link: https://leetcode.com/problems/binary-search/
// Difficulty: Easy

// Approach:
// We use the Binary Search algorithm to efficiently find the target value
// in a sorted array.
//
// - Start with two pointers: `begin` and `end`.
// - Find the middle index.
// - If the middle element matches the target, return its index.
// - If the middle element is greater than the target,
//   search in the left half.
// - Otherwise, search in the right half.
// - If the target is not found, return -1.
//
// Time Complexity: O(log n)
// Space Complexity: O(log n) due to recursive calls

# include <vector>
using namespace std;
class Solution {
public:

    int binSearch(int begin, int end, vector<int>& nums, int target){
        if (begin <= end){
            int mid = (begin + end) / 2;

            if (nums[mid] == target){
                return mid;
            } 
            else if (nums[mid] > target){
                return binSearch(begin, mid - 1, nums, target);
            } 
            else {
                return binSearch(mid + 1, end, nums, target);
            }
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        return binSearch(0, nums.size() - 1, nums, target);
    }
};