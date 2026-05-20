// Problem: Search a 2D Matrix
// Link: https://leetcode.com/problems/search-a-2d-matrix/
// Difficulty: Medium

// Approach:
// We treat the 2D matrix as a flattened sorted array and perform binary search.
//
// - Compute the total number of elements as rows * cols.
// - Initialize left (`l`) and right (`r`) pointers.
// - While l <= r:
//   - Compute mid index.
//   - Map mid back to 2D coordinates: row = mid / cols, col = mid % cols.
//   - Compare the value at matrix[row][col] with the target.
//   - If equal, return true.
//   - If greater, search the left half.
//   - If smaller, search the right half.
// - Return false if the target is not found.
//
// Time Complexity: O(log(m*n)), where m = number of rows, n = number of columns
// Space Complexity: O(1)

# include <vector>
using namespace std;

class Solution {
public:

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int l = 0, r = rows * cols - 1;

        while (l <= r){
            int mid = (l + r) / 2;

            int val = matrix[mid / cols][mid % cols];
            if (val == target) return true;
            else if (val > target){
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return false;
    }
};