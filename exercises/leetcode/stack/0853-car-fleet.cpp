// Problem: Car Fleet
// Link: https://leetcode.com/problems/car-fleet/
// Difficulty: Medium

// Approach:
// We first pair each car's position with its speed and sort them in descending order of position (closest to target first).
// We then use a stack to track fleets based on the time it takes for each car to reach the target.
// For each car:
// - Compute the time to reach the target.
// - If the stack is empty or the current car takes longer than the fleet on top of the stack, it forms a new fleet and is pushed onto the stack.
// - Otherwise, it joins the fleet on top of the stack (no push needed).
// At the end, the stack size represents the total number of car fleets that will arrive at the target.

// Time Complexity: O(n log n), due to sorting n cars
// Space Complexity: O(n), for the stack storing fleet times


# include <vector>
# include <stack>
# include <algorithm>
using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int,int>> cars;
        for (int i = 0; i < position.size(); i++)
            cars.push_back({position[i], speed[i]});

        sort(cars.rbegin(), cars.rend());

        stack<double> st;
        for (auto& c : cars) {
            double time = (double)(target - c.first) / c.second;
            if (st.empty() || time > st.top()) 
                st.push(time);
        }

        return st.size();
    }
};
