// Problem: Minimum Window Substring
// Link: https://leetcode.com/problems/minimum-window-substring
// Difficulty: Hard

// Approach:
// We use a sliding window with two pointers to find the minimum window
// in string s that contains all the characters of string t.
//
// Steps:
// 1. Count the frequency of characters in t using an unordered_map.
// 2. Use two pointers (l, r) to represent the window in s.
// 3. Expand the window by moving r, updating the window frequency map.
// 4. Track how many unique characters in t have been fully satisfied in the window.
// 5. Once all characters are satisfied (have == need), try to shrink the window from the left (l)
//    to minimize the window size, updating the result if smaller.
// 6. Return the substring corresponding to the smallest valid window.
//
// Time Complexity: O(n + m) - traverse s once, t once
// Space Complexity: O(n + m) - frequency maps for s and t

#include <string>
#include <unordered_map>
#include <climits>
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

    string minWindow(string s, string t) {
        unordered_map<char, int> mp_t = getFreq(t);

        int l = 0; 
        int have = 0;
        int need = mp_t.size();
        int minSize = INT_MAX;
        int minL;
        unordered_map<char, int> mp_window;
        
        for (int r = 0; r < s.length(); r++){
            mp_window[s[r]]++;
            if (mp_window[s[r]] == mp_t[s[r]]){
                have++;
            }
            while(have == need){
                if (r - l + 1 < minSize) {
                    minSize = r - l + 1;
                    minL = l; 
                }
                mp_window[s[l]]--;
                if (mp_window[s[l]] < mp_t[s[l]]){
                    have--;
                }
                l++;
            }
        }

        string res = "";
        if (minSize == INT_MAX){
            minSize = 0;
        }
        for (int i = minL; i < minL + minSize; i++){
            res.push_back(s[i]);
        }

        return res;

    }
};