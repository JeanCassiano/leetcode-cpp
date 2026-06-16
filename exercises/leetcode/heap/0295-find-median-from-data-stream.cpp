// Problem: Find Median from Data Stream
// Link: https://leetcode.com/problems/find-median-from-data-stream/
// Difficulty: Hard
//
// Approach:
// We use two heaps to maintain the median:
// - smallHeap: max heap storing the smaller half of numbers
// - largeHeap: min heap storing the larger half of numbers
//
// Balance Property:
// - smallHeap.size() == largeHeap.size() or smallHeap.size() == largeHeap.size() + 1
//
// addNum:
// - Add num to smallHeap (max heap)
// - If largeHeap is not empty and top of smallHeap > top of largeHeap, swap
// - Balance the sizes: ensure smallHeap.size() <= largeHeap.size() + 1
//
// findMedian:
// - If sizes are equal: median = (top of smallHeap + top of largeHeap) / 2
// - If smallHeap has one more: median = top of smallHeap
// - Else: median = top of largeHeap
//
// Time Complexity:
// - addNum: O(log n)
// - findMedian: O(1)
//
// Space Complexity: O(n)
//   - n = number of elements added

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class MedianFinder {
private:
    priority_queue<int, vector<int>, less<int>> smallHeap;
    priority_queue<int, vector<int>, greater<int>> largeHeap;

public:
    MedianFinder() {}

    void addNum(int num) {
        // Add to max heap (smaller half)
        smallHeap.push(num);

        // Ensure all elements in smallHeap <= all elements in largeHeap
        if (!largeHeap.empty() && smallHeap.top() > largeHeap.top()) {
            largeHeap.push(smallHeap.top());
            smallHeap.pop();
        }

        // Balance the heaps: smallHeap should have at most 1 more element
        if (smallHeap.size() > largeHeap.size() + 1) {
            largeHeap.push(smallHeap.top());
            smallHeap.pop();
        }

        // Ensure largeHeap doesn't have more elements than smallHeap
        if (largeHeap.size() > smallHeap.size() + 1) {
            smallHeap.push(largeHeap.top());
            largeHeap.pop();
        }
    }

    double findMedian() {
        // If both heaps have same size, median is average of tops
        if (smallHeap.size() == largeHeap.size()) {
            return (largeHeap.top() + smallHeap.top()) / 2.0;
        }
        // If smallHeap has one more element, it's the median
        else if (smallHeap.size() > largeHeap.size()) {
            return smallHeap.top();
        }
        // Else largeHeap has one more element
        else {
            return largeHeap.top();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
