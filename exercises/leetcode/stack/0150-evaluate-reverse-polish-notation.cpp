// Problem: Evaluate Reverse Polish Notation
// Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/
// Difficulty: Medium

// Approach:
// We use a stack to evaluate the expression in Reverse Polish Notation (RPN).
// For each token in the input:
// - If the token is a number, we push it onto the stack.
// - If the token is an operator (+, -, *, /), we pop the top two numbers from the stack, 
//   apply the operator, and push the result back onto the stack.
// At the end, the stack contains exactly one element, which is the result of the expression.

// Time Complexity: O(n), where n is the number of tokens
// Space Complexity: O(n), due to the stack used to store intermediate values

#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stack;
        for (const auto& c : tokens){
            if (c == "+" || c == "-" || c == "*" || c == "/"){
                int temp1 = stack.top();
                stack.pop();
                int temp2 = stack.top();
                stack.pop();
                if (c == "+") stack.push(temp2 + temp1);
                else if (c == "-") stack.push(temp2 - temp1);
                else if (c == "*") stack.push(temp2 * temp1);
                else stack.push(temp2 / temp1);
            } else {
                stack.push(std::stoi(c));
            }
        }
        return stack.top();
    }
};