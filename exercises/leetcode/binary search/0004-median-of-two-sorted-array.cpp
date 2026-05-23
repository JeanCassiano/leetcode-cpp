// Problem: Median of Two Sorted Arrays
// Link: https://leetcode.com/problems/median-of-two-sorted-arrays/
// Difficulty: Hard

// Approach:
// We use Binary Search on the smaller array to partition both arrays
// into left and right halves such that:
//
// - Every element in the left partition <= every element in the right partition.
// - The left partition contains half of the total elements.
//
// Steps:
// - Always perform binary search on the smaller array for efficiency.
// - Partition arrays using indices i and j:
//      i -> partition index for A
//      j -> partition index for B
//
// Partition values:
// - Aleft  = largest value on left side of A
// - Aright = smallest value on right side of A
// - Bleft  = largest value on left side of B
// - Bright = smallest value on right side of B
//
// Correct partition condition:
//      Aleft <= Bright
//      Bleft <= Aright
//
// If partition is correct:
// - For odd total length:
//      median = max(Aleft, Bleft)
// - For even total length:
//      median = average of:
//          max(Aleft, Bleft)
//          min(Aright, Bright)
//
// Otherwise:
// - If Aleft > Bright:
//      move search left
// - Else:
//      move search right
//
// Time Complexity:
// - O(log(min(n, m)))
//
// Space Complexity:
// - O(1)

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& A = nums1;
        vector<int>& B = nums2;

        int total = A.size() + B.size();
        int half = (total + 1) / 2;

        // Ensure A is the smaller array
        if (B.size() < A.size()) {
            swap(A, B);
        }

        int l = 0;
        int r = A.size();

        while (l <= r) {
            int i = (l + r) / 2;
            int j = half - i;

            int Aleft  = i > 0 ? A[i - 1] : INT_MIN;
            int Aright = i < A.size() ? A[i] : INT_MAX;

            int Bleft  = j > 0 ? B[j - 1] : INT_MIN;
            int Bright = j < B.size() ? B[j] : INT_MAX;

            // Correct partition found
            if (Aleft <= Bright && Bleft <= Aright) {

                // Odd total length
                if (total % 2 != 0) {
                    return max(Aleft, Bleft);
                }

                // Even total length
                return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
            }

            // Move binary search
            else if (Aleft > Bright) {
                r = i - 1;
            } else {
                l = i + 1;
            }
        }

        return -1;
    }
};