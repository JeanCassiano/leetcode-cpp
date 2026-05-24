// Problem: Longest Repeating Character Replacement
// Link: https://leetcode.com/problems/longest-repeating-character-replacement/description/
// Difficulty: Medium

// We use a HashMap to count the frequency of characters in the current window
// We maintain a sliding window with left (l) and right (r) pointers
// maxf keeps track of the maximum frequency of any character in the window
// If the number of characters to replace (window size - maxf) exceeds k, we shrink the window from the left
// At each step, we update the result with the size of the current valid window

// Time Complexity: O(n)
// Space Complexity: O(26) ~ O(1), because at most we store 26 letters


#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;
class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> count;
        int l = 0;           // left of the window
        int maxf = 0;        // max frequency of any char in the window
        int res = 0;         // result
        
        for (int r = 0; r < s.size(); r++) {
            // 1. Expand: add s[r] to the window
            count[s[r]]++;
            maxf = max(maxf, count[s[r]]);
            
            // 2. Check if the window is valid
            int window_size = r - l + 1;
            int chars_to_replace = window_size - maxf;
            
            // 3. If invalid, shrink the window from the left
            while (chars_to_replace > k) {
                count[s[l]]--;
                l++;
                window_size = r - l + 1;
                chars_to_replace = window_size - maxf;
            }
            
            // 4. Update result
            res = max(res, window_size);
        }

        return res;
    }
};
