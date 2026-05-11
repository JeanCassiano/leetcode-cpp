// Problem: Best Time to Buy and Sell Stock
// Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// Difficulty: Easy

// Approach:
// We use a greedy strategy while scanning the array once.
//
// The main observation is:
//
// profit = sellPrice - buyPrice
//
// To maximize the profit when selling today,
// we should have bought at the lowest price seen before today.
//
// During traversal:
// - Keep track of the minimum price encountered so far
// - Compute the profit if we sell at the current price
// - Update the maximum profit found
//
// At each step:
// - minPrice represents the best day to buy so far
// - prices[i] represents the current selling price
//
// This allows us to efficiently compute the best possible
// transaction in a single pass without checking all pairs.

// Time Complexity: O(n)
// Space Complexity: O(1)

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < prices.size(); i++) {
            minPrice = min(prices[i], minPrice);

            int profit = prices[i] - minPrice;

            maxProfit = max(maxProfit, profit);
        }

        return maxProfit;
    }
};