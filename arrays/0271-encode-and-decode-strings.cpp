// Problem: Encode and Decode Strings
// Link: https://leetcode.com/problems/encode-and-decode-strings/
// Difficulty: Medium

// Approach:
// The goal is to serialize a list of strings into a single string and then deserialize it back
// without losing any information, even if strings contain special characters.
//
// We use a length-prefixed encoding scheme:
// Each string is encoded as: "<length>#<string>"
//
// Example:
// ["leet", "code"] → "4#leet4#code"
//
// Encoding:
// For each string, append its length, a delimiter '#', and the string itself.
//
// Decoding:
// We scan the encoded string from left to right.
// 1. Read digits until we reach '#', this gives the length of the next string.
// 2. Skip '#'
// 3. Extract exactly 'len' characters as the original string.
// 4. Move the pointer forward and repeat.
//
// This ensures unambiguous reconstruction regardless of string content.
//
// Time Complexity: O(n), where n is the total number of characters across all strings.
// Space Complexity: O(1) extra space (excluding output list).

#include <vector>
#include <string>

using namespace std;

class Solution {
public:

    string encode(vector<string>& strs) {
        string encoded = "";

        for (const string& s : strs) {
            encoded += to_string(s.size());
            encoded += "#";
            encoded += s;
        }

        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> decoded;
        int i = 0;

        while (i < s.size()) {
            int j = i;

            while (s[j] != '#') {
                j++;
            }

            int len = stoi(s.substr(i, j - i));
            j++; // skip '#'

            decoded.push_back(s.substr(j, len));
            i = j + len;
        }

        return decoded;
    }
};