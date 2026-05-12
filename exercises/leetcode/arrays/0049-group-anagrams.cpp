// Problem: Group Anagrams
// Link: https://leetcode.com/problems/group-anagrams/
// Difficulty: Medium

// Approach:
// We use an unordered_map where the key is a sorted version of the string (the "signature")
// and the value is a vector of all original strings that share that signature.
// By sorting each string, all anagrams become identical, allowing us to group them easily.
// Finally, we collect all the grouped vectors from the map and return them.

// Time Complexity: O(n * k log k), where n is the number of strings and k is the maximum length of a string.
// Space Complexity: O(n * k), to store the strings in the hash map.

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Map to store sorted string as key and original strings as values
        unordered_map<string, vector<string>> anagramMap;
    
        for (string s : strs) {
            string key = s;
            // Sort the string to create a unique key for all its anagrams
            sort(key.begin(), key.end());

            // Add the original string to the corresponding group
            anagramMap[key].push_back(s);
        }

        // Prepare the result vector by extracting values from the map
        vector<vector<string>> output;
        for (auto const& [key, group] : anagramMap) {
            output.push_back(group);
        }

        return output;
    }
};