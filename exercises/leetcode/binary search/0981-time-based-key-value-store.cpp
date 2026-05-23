// Problem: Time Based Key-Value Store
// Link: https://leetcode.com/problems/time-based-key-value-store/
// Difficulty: Medium

// Approach:
// We use a hash map where:
// - key -> vector of {timestamp, value} pairs.
//
// Since timestamps for each key are strictly increasing,
// we can append new values directly into the vector.
//
// For retrieval:
// - Use binary search to find the latest timestamp
//   less than or equal to the given timestamp.
// - Return the corresponding value.
// - If no valid timestamp exists, return an empty string.
//
// Steps for get():
// - Retrieve the vector associated with the key.
// - Perform binary search on timestamps.
// - If values[mid].timestamp <= target timestamp:
//      store the value and search right for a later valid timestamp.
// - Else search left.
// - Return the best found result.
//
// Time Complexity:
// - set(): O(1)
// - get(): O(log n)
//
// Space Complexity:
// - O(n)

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> keyStore;

public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        keyStore[key].emplace_back(timestamp, value);
    }

    string get(string key, int timestamp) {
        auto& values = keyStore[key];

        int left = 0;
        int right = values.size() - 1;

        string result = "";

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (values[mid].first <= timestamp) {
                result = values[mid].second;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;
    }
};