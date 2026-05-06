// Problem: Longest Consecutive Sequence
// Link: https://leetcode.com/problems/longest-consecutive-sequence/
// Difficulty: Medium

// Approach:
// We use an unordered_set to allow O(1) lookups.
// For each number, we only start counting a sequence if it is the beginning
// of that sequence (i.e., num - 1 does not exist in the set).
// Then we expand forward (num + 1, num + 2, ...) to measure the full length.

// Time Complexity: O(n) - each element is visited at most twice
// Space Complexity: O(n)

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int longest = 0;

        for (int num : s) {
            if (!s.count(num - 1)) { // start of a sequence
                int current = num;
                int length = 1;

                while (s.count(current + 1)) {
                    current++;
                    length++;
                }

                longest = max(longest, length);
            }
        }

        return longest;
    }
};