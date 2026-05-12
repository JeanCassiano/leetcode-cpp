// Problem: Top K Frequent Elements
// Link: https://leetcode.com/problems/top-k-frequent-elements/
// Difficulty: Medium

// Approach:
// First, we count the frequency of each number using an unordered_map,
// where the key is the number and the value is its frequency.
//
// Then, we use a bucket sort idea:
// - We create a vector of vectors (buckets), where the index represents frequency.
// - Each bucket[i] stores all numbers that appear exactly i times.
//
// Since the maximum possible frequency of any number is nums.size(),
// we allocate buckets of size (n + 1).
//
// After filling the buckets, we iterate from the highest possible frequency
// down to 1, collecting elements until we have k results.
// This ensures we always pick the most frequent elements first.
//
// Time Complexity: O(n), where n is the size of nums. We traverse nums once to build the map,
// then iterate through the map and buckets once. Overall linear time.
//
// Space Complexity: O(n), due to the unordered_map and the bucket array in the worst case.

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        
        for (int i = 0; i < nums.size(); i++) {
            count[nums[i]]++;
        }

        vector<vector<int>> buckets(nums.size() + 1);

        for (auto& [num, freq] : count) {
            buckets[freq].push_back(num);
        }

        vector<int> result;

        for (int i = nums.size(); i > 0; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);

                if (result.size() == k) {
                    return result;
                }
            }
        }

        return result;
    }
};