// Problem: Valid Anagram
// Link: https://leetcode.com/problems/valid-anagram/
// Difficulty: Easy

// Approach:
// First, check if the lengths of the two strings are different; if so, return false.
// Use a fixed-size array (or vector) of 26 integers to track character frequencies.
// Iterate through both strings simultaneously: increment the count for characters 
// in the first string and decrement for characters in the second string. 
// We map each character to an index from 0 to 25 using its ASCII value (char - 'a').
// Finally, iterate through the frequency array. If any count is non-zero, 
// it means there is a mismatch in character quantities, so we return false.

// Time Complexity: O(n), where n is the length of the strings. We traverse the strings once.
// Space Complexity: O(1), because the frequency array size is always fixed at 26, regardless of the input size.

#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()){
            return false;
        }
        vector<int> count(26, 0);
        for (int i = 0; i < s.size(); i++){
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        for (int c : count){
            if (c != 0){
                return false;
            }
        }
        return true;
    }
};