// Problem: Weekly Contest 413 Problem 4
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
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> mx(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--) {
            mx[i][i] = nums[i];
            vector<int> f = nums;
            for (int j = i + 1; j < n; j++) {
                f[j] ^= f[j - 1];
                mx[i][j] = max(f[j], max(mx[i + 1][j], mx[i][j - 1]));
            }
        }

        vector<int> ans;
        for (auto& q : queries) {
            ans.push_back(mx[q[0]][q[1]]);
        }
        return ans;
    }
};
