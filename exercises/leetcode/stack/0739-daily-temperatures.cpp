// Problem: Daily Temperatures
// Link: https://leetcode.com/problems/daily-temperatures/
// Difficulty: Medium

// Approach:
// We use a stack to keep track of temperatures and their indices.
// For each temperature in the input array:
// - While the stack is not empty and the current temperature is higher than the temperature on top of the stack,
//   we pop the stack and calculate the number of days until a warmer temperature for the popped index.
// - We then push the current temperature and its index onto the stack.
// At the end, the result array contains the number of days to wait for a warmer temperature for each day.

// Time Complexity: O(n), where n is the number of temperatures
// Space Complexity: O(n), due to the stack used to store temperature-index pairs

# include <vector>
# include <stack>

using namespace std;
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int, int>> st;
        vector<int> res(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); i++){
            int temp = temperatures[i];
            while (!st.empty() && temp > st.top().first){
                auto pair = st.top();
                st.pop();
                res[pair.second] = i - pair.second;
            }
            st.push({temp, i});
        }
        return res;
    }
};