// Problem: Valid Sudoku
// Link: https://leetcode.com/problems/valid-sudoku/
// Difficulty: Medium

// Approach:
// We track seen numbers using three hash sets: rows, columns, and 3x3 boxes.
// For each cell, we check if the number already exists in its row, column, or box.
// If it does, the board is invalid. Otherwise, we insert it into the corresponding sets.

// Time Complexity: O(81) - constant
// Space Complexity: O(81) - constant

#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<unordered_set<char>> rows(9), cols(9), boxes(9);

        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (board[i][j] != '.'){
                    char num = board[i][j];
                    int boxIndex = (i / 3) * 3 + (j / 3);
                    if (rows[i].count(num) ||
                        cols[j].count(num) ||
                        boxes[boxIndex].count(num)) {
                        return false;
                    }

                    rows[i].insert(num);
                    cols[j].insert(num);
                    boxes[boxIndex].insert(num);
                }
            }
        }
        return true;
    }
};
