// Problem: Valid Parentheses
// Link: https://leetcode.com/problems/valid-parentheses/
// Difficulty: Easy

// Approach:
// We use a stack to keep track of opening brackets. For every character in the string:
// - If it is a closing bracket, we check whether the stack is empty or the top of the stack 
//   does not match the corresponding opening bracket. If either is true, the string is invalid.
// - If it is an opening bracket, we push it onto the stack.
// After processing all characters, the string is valid only if the stack is empty.

// Time Complexity: O(n), where n is the length of the string
// Space Complexity: O(n), in the worst case all characters are opening brackets

#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char,char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        for (const auto& c : s){
            if (pairs.count(c)){
                if (st.empty() || st.top() != pairs[c]) return false;
                st.pop();
            } else {
                st.push(c);
            }
        }

        return st.empty();
    }
};