// Problem: Koko Eating Bananas
// Link: https://leetcode.com/problems/koko-eating-bananas/
// Difficulty: Medium

// Approach:
// We use binary search to find the minimum eating speed `k` that allows
// Koko to finish all banana piles within `h` hours.
//
// - Set the search range: `l = 1` (minimum possible speed) and 
//   `r = max(piles)` (maximum pile size).
// - While l <= r:
//   - Compute mid `k` as candidate speed.
//   - Calculate total time to eat all piles at speed `k`, using ceiling division.
//   - If totalTime <= h, we can try a slower speed: update res = k and r = k - 1.
//   - Otherwise, try a faster speed: l = k + 1.
// - Return res, the minimum valid eating speed.
//
// Time Complexity: O(n log m), where n = number of piles, m = max pile size
// Space Complexity: O(1)

# include <vector>
# include <algorithm>
# include <cmath>
using namespace std;
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1;
        int r = *max_element(piles.begin(), piles.end());
        int res = r;

        while (l <= r){
            int k = (l + r) / 2;

            long long totalTime = 0;
            for (int p : piles){
                totalTime += ceil(static_cast<double>(p) / k);
            }

            if (totalTime <= h){
                res = k;
                r = k - 1;
            } else {
                l = k + 1;
            }
        }
        return res;
    }
};