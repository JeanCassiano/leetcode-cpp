// Problem: Search in Rotated Sorted Array
// Link: https://leetcode.com/problems/search-in-rotated-sorted-array/
// Difficulty: Medium

// Approach:
// We perform a modified binary search to find the target in a rotated sorted array.
//
// - Initialize left (`l`) and right (`r`) pointers to the start and end of the array.
// - While l <= r:
//   - Compute mid index.
//   - If nums[mid] equals target, return mid.
//   - Check which half is sorted:
//     1. If nums[l] <= nums[mid], the left half is sorted.
//        - If target lies within this sorted left half, move r = mid - 1.
//        - Else, search the right half by moving l = mid + 1.
//     2. Else, the right half is sorted.
//        - If target lies within the sorted right half, move l = mid + 1.
//        - Else, search the left half by moving r = mid - 1.
// - Return -1 if the target is not found.
//
// Time Complexity: O(log n), where n = number of elements.
// Space Complexity: O(1)

#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        
        while (l <= r) {
            int mid = (l + r) / 2; // Compute middle index

            // Check if mid is the target
            if (nums[mid] == target) return mid;

            // Determine which half is sorted
            if (nums[l] <= nums[mid]) {
                // Left half is sorted
                if (target >= nums[l] && target < nums[mid])
                    r = mid - 1; // Target is in left half
                else
                    l = mid + 1; // Target is in right half
            } else {
                // Right half is sorted
                if (target > nums[mid] && target <= nums[r])
                    l = mid + 1; // Target is in right half
                else
                    r = mid - 1; // Target is in left half
            }
        }

        return -1; // Target not found
    }
};