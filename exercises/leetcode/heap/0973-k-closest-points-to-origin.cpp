// Problem: K Closest Points to Origin
// Link: https://leetcode.com/problems/k-closest-points-to-origin/
// Difficulty: Medium
//
// Approach:
// We use a min heap to find the k closest points to the origin.
//
// - Calculate the squared distance from each point to the origin.
//   (We use squared distance to avoid floating-point calculations)
// - Store pairs of (distance, index) in a min heap.
// - Extract the k smallest distances from the heap.
// - Return the corresponding points.
//
// Time Complexity: O(n log n)
//   - n = number of points
//   - Building the heap takes O(n log n)
//   - Extracting k elements takes O(k log n)
//
// Space Complexity: O(n)
//   - Space used by the min heap

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;

        // Calculate squared distances and store in min heap
        for (int i = 0; i < points.size(); i++) {
            int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            minHeap.push({dist, i});
        }

        vector<vector<int>> res;
        // Extract k closest points
        while (k > 0) {
            k--;
            int idx = minHeap.top().second;
            minHeap.pop();
            res.push_back(points[idx]);
        }

        return res;
    }
};
