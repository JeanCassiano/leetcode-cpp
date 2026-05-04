## Overview

This repository serves as a personal knowledge base and reference for solving algorithmic and data structure problems using modern C++. Each solution is written with attention to:

* Readability and clean code principles
* Time and space complexity analysis
* Multiple approaches when relevant (brute force → optimized)
* Idiomatic use of C++ (STL, templates, memory awareness)

## Structure

Problems are organized by topic and/or difficulty for easier navigation:

```
leetcode-cpp/
├── arrays/
├── strings/
├── linked-lists/
├── trees/
├── graphs/
├── dynamic-programming/
├── backtracking/
└── ...
```

Each problem typically includes:

* Problem name and link
* Description (brief summary)
* Approach explanation
* Complexity analysis
* C++ implementation

## Example Format

```cpp
// Problem: Two Sum
// Link: https://leetcode.com/problems/two-sum/
// Difficulty: Easy

// Approach:
// Use a hash map to store visited elements.
// For each element, check if the complement exists.

// Time Complexity: O(n)
// Space Complexity: O(n)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (map.count(complement)) {
                return {map[complement], i};
            }
            map[nums[i]] = i;
        }
        return {};
    }
};
```

## License

This repository is for educational purposes. Feel free to use the code as reference, but avoid copying solutions directly in competitive environments.
