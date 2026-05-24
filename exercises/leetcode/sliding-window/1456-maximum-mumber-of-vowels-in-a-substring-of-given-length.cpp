// Problem: Maximum Number of Vowels in a Substring of Given Length
// Link: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length
// Difficulty: Medium

// Approach:
// We use a sliding window strategy to efficiently find the substring of length k
// that contains the maximum number of vowels.
//
// Steps:
// 1. Use an unordered_set to store vowels for O(1) lookup.
// 2. Count the vowels in the first k characters (initial window).
// 3. Slide the window one character at a time:
//    - Add 1 if the new character entering the window is a vowel.
//    - Subtract 1 if the character leaving the window is a vowel.
//    - Keep track of the maximum count of vowels seen so far.
//
// Time Complexity: O(n) - traverse the string once
// Space Complexity: O(1) - the set of vowels is fixed size

#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int l = 0;
        int res = 0;
        
        // Initial window
        for (int i = 0; i < k; i++){
            if (vowels.count(s[i])){
                res++;
            }
        }
        int temp = res;

        // Slide the window
        for (int r = k; r < s.length(); r++){
            if (vowels.count(s[r])){
                temp++;
            }
            if (vowels.count(s[l])){
                temp--;
            }
            l++;
            res = max(res, temp);
        }
        return res;
    }
};