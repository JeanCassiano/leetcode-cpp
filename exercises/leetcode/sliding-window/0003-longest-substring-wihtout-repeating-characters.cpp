// Problem: Longest Substring Without Repeating Characters
// Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
// Difficulty: Medium

// We create a HashMap to store the character and its position on the string
// Each iteration we look if the characters it was already seen 
// We update the variables, where l is the index of the repeated character + 1
// We update the maximum (the difference between the right pointer and the left pointer + 1)

// Time Complexity: O(n)
// Space Complexity: O(n)


#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;
        int l = 0, res = 0;

        for (int r = 0; r < s.size(); r++) {
            if (mp.find(s[r]) != mp.end()) {
                l = max(mp[s[r]] + 1, l);
            }
            mp[s[r]] = r;
            res = max(res, r - l + 1);
        }
        return res;
    }
};