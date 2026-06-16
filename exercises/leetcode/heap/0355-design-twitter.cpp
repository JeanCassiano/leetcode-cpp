// Problem: Design Twitter
// Link: https://leetcode.com/problems/design-twitter/
// Difficulty: Medium
//
// Approach:
// We design a Twitter system with three main operations:
// 1. Post a tweet
// 2. Get news feed (10 most recent tweets from user and followed users)
// 3. Follow/Unfollow a user
//
// Data Structures:
// - tweetMap: stores tweets for each user (limited to 10 most recent)
// - followMap: stores the set of users that each user follows
// - count: global counter for tweet timestamp (decreasing for recency)
//
// getNewsFeed Strategy:
// - If following < 10 users: use min heap to merge tweets
// - If following >= 10 users: use max heap to get top 10, then convert to min heap
// - Use merge of multiple sorted lists approach
//
// Time Complexity:
// - postTweet: O(1)
// - getNewsFeed: O(k log 10) where k = number of followees
// - follow/unfollow: O(1)
//
// Space Complexity: O(n * 10 + m)
//   - n = number of users with tweets
//   - m = total number of followers across all users

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Twitter {
private:
    int count;
    unordered_map<int, vector<pair<int, int>>> tweetMap;
    unordered_map<int, unordered_set<int>> followMap;

public:
    Twitter() {
        count = 0;
    }

    void postTweet(int userId, int tweetId) {
        tweetMap[userId].push_back({count, tweetId});
        // Keep only the 10 most recent tweets
        if (tweetMap[userId].size() > 10) {
            tweetMap[userId].erase(tweetMap[userId].begin());
        }
        count--;
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        // User automatically follows themselves
        followMap[userId].insert(userId);

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;

        // Optimization: if following >= 10 users, use max heap first
        if (followMap[userId].size() >= 10) {
            priority_queue<vector<int>> maxHeap;
            for (auto f : followMap[userId]) {
                if (!tweetMap.count(f)) continue;
                int idx = tweetMap[f].size() - 1;
                auto& p = tweetMap[f][idx];
                maxHeap.push({-p.first, p.second, f, idx - 1});
                if (maxHeap.size() > 10) maxHeap.pop();
            }
            // Convert max heap to min heap
            while (!maxHeap.empty()) {
                auto t = maxHeap.top();
                maxHeap.pop();
                minHeap.push({-t[0], t[1], t[2], t[3]});
            }
        } else {
            // Directly add tweets to min heap
            for (auto f : followMap[userId]) {
                if (!tweetMap.count(f)) continue;
                int idx = tweetMap[f].size() - 1;
                auto& p = tweetMap[f][idx];
                minHeap.push({p.first, p.second, f, idx - 1});
            }
        }

        // Extract 10 most recent tweets
        while (!minHeap.empty() && res.size() < 10) {
            auto t = minHeap.top();
            minHeap.pop();
            res.push_back(t[1]);

            // Add next tweet from the same user
            int idx = t[3];
            if (idx >= 0) {
                auto& p = tweetMap[t[2]][idx];
                minHeap.push({p.first, p.second, t[2], idx - 1});
            }
        }

        return res;
    }

    void follow(int followerId, int followeeId) {
        followMap[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        if (followMap[followerId].count(followeeId)) {
            followMap[followerId].erase(followeeId);
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId, tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId, followeeId);
 * obj->unfollow(followerId, followeeId);
 */
