// Problem: Valid Palindrome
// Link: https://leetcode.com/problems/valid-palindrome/
// Difficulty: Easy

// Approach:
// We use a two-pointer technique directly on the original string (no extra space).
// We move pointers inward, skipping non-alphanumeric characters.
// Then we compare characters in a case-insensitive way using tolower().
// If all matched pairs are equal, the string is a palindrome.

// Time Complexity: O(n)
// Space Complexity: O(1)

#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {

        int i = 0;
        int j = s.length() - 1;

        while (i < j) {

            while (i < j && !isalnum(s[i])) {
                i++;
            }

            while (i < j && !isalnum(s[j])) {
                j--;
            }

            if (tolower(s[i]) != tolower(s[j])) {
                return false;
            }

            i++;
            j--;
        }

        return true;
    }
};