// Problem: Permutation in String
// Link: https://leetcode.com/problems/permutation-in-string
// Difficulty: Medium

// Approach:
// We use a sliding window with two pointers to check if any substring of s2
// is a permutation of s1.
//
// Steps:
// 1. Count the frequency of characters in s1 using an unordered_map.
// 2. Use two pointers (l, r) to represent the current window in s2.
// 3. Expand the window by moving r, updating the window frequency map.
// 4. Track how many unique characters have the exact frequency required (have).
// 5. If 'have' equals 'need' (all characters matched), return true.
// 6. If the window size exceeds s1.size(), shrink it from the left (l) and update counts.
// 7. If no valid window is found, return false.
//
// Time Complexity: O(n) - traverse s2 once
// Space Complexity: O(1) - frequency maps of characters (constant alphabet size)

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    unordered_map<char, int> getFreq(string s){
        unordered_map<char, int> mp;
        for (const auto& c : s){
            mp[c]++;
        }
        return mp;
    }
    
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> freq_s1 = getFreq(s1);
        int have = 0;
        int need = freq_s1.size();
        int l = 0;
        unordered_map<char, int> window;
        for (int r = 0; r < s2.size(); r++){
            window[s2[r]]++;
            if (window[s2[r]] == freq_s1[s2[r]]){
                have++;
            }
            if (have == need){
                return true;
            }
            if (r - l + 1 == s1.size()){
                if (window[s2[l]] == freq_s1[s2[l]]){
                    have--;
                }
                window[s2[l]]--;
                l++;
            }
        }
        return false;
    }
};