// Problem: Task Scheduler
// Link: https://leetcode.com/problems/task-scheduler/
// Difficulty: Medium
//
// Approach:
// We use a max heap to track task frequencies and a queue to manage
// tasks in cooldown. We optimize by skipping idle time when the heap is empty.
//
// - Count the frequency of each task using an array (26 letters).
// - Use a max heap to always process the most frequent task.
// - Use a queue to track tasks in cooldown (paired with the time they can be executed again).
// - For each time unit:
//   - If no tasks are available, jump to the next available time.
//   - Execute the most frequent task and decrease its frequency.
//   - If frequency > 0, add it to cooldown for n time units.
//   - Check if any task in cooldown is ready to be executed.
// - Continue until all tasks are done.
//
// Time Complexity: O(n log k)
//   - n = total number of tasks
//   - k = number of unique tasks (max 26)
//
// Space Complexity: O(k)
//   - Space used by the max heap and cooldown queue

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        // Count frequency of each task
        for (char task : tasks) {
            count[task - 'A']++;
        }

        priority_queue<int> maxHeap;
        // Add all non-zero frequencies to max heap
        for (int cnt : count) {
            if (cnt > 0) {
                maxHeap.push(cnt);
            }
        }

        int time = 0;
        queue<pair<int, int>> q;
        // Process tasks until all are done
        while (!maxHeap.empty() || !q.empty()) {
            time++;

            // If no tasks available in heap, jump to next available time
            if (maxHeap.empty()) {
                time = q.front().second;
            } else {
                // Execute the most frequent task
                int cnt = maxHeap.top() - 1;
                maxHeap.pop();
                // If task still has remaining executions, add to cooldown
                if (cnt > 0) {
                    q.push({cnt, time + n});
                }
            }

            // Check if any task in cooldown is ready
            if (!q.empty() && q.front().second == time) {
                maxHeap.push(q.front().first);
                q.pop();
            }
        }

        return time;
    }
};
