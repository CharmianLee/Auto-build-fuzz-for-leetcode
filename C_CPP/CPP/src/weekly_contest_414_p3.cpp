// Problem: Weekly Contest 414 Problem 3
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }
    long long findMaximumScore(vector<int>& nums) {
        long long ans = 0;
        int mx = 0;
        for (int i = 0; i + 1 < nums.size(); i++) {
            mx = max(mx, nums[i]);
            ans += mx;
        }
        return ans;
    }
};
