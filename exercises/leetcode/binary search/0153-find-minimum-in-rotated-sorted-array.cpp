// Problem: Find Minimum in Rotated Sorted Array
// Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// Difficulty: Medium

// Approach:
// We perform a modified binary search to find the minimum element in a rotated sorted array.
//
// - Initialize left (`l`) and right (`r`) pointers to the start and end of the array.
// - Initialize `minInt` to INT_MAX to keep track of the minimum value found so far.
// - While l <= r:
//   - Compute mid index.
//   - If nums[mid] > nums[r], the minimum must be in the right half (excluding mid).
//     -> Move l to mid + 1.
//   - Else, the minimum is in the left half (including mid).
//     -> Move r to mid - 1.
//   - Update minInt with the smaller value between current minInt and nums[mid].
// - Return minInt after the loop ends.
//
// Time Complexity: O(log n) in the average case, where n is the number of elements.
// Space Complexity: O(1)

#include <vector>
#include <climits> // for INT_MAX
using namespace std;

class Solution {
public:
    int findMin(vector<int> &nums) {
        int l = 0;
        int r = nums.size() - 1;
        int minInt = INT_MAX; // Initialize minimum value to maximum integer

        while (l <= r){
            int mid = (l + r) / 2; // Compute middle index

            // If middle element is greater than rightmost element,
            // minimum must be in the right half
            if (nums[mid] > nums[r]){
                l = mid + 1;
            } else {
                // Otherwise, minimum is in the left half
                r = mid - 1;
            }

            // Update minimum value found so far
            minInt = min(minInt, nums[mid]);
        } 

        return minInt; // Return the minimum element
    }
};