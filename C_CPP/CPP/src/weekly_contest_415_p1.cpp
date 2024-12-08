// Problem: Weekly Contest 415 Problem 1
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
    vector<int> getSneakyNumbers(vector<int>& nums) {
        int n = nums.size() - 2;
        int xor_all = n ^ (n + 1); // n 和 n+1 多异或了
        for (int i = 0; i < nums.size(); i++) {
            xor_all ^= i ^ nums[i];
        }
        int shift = __builtin_ctz(xor_all);

        vector<int> ans(2);
        for (int i = 0; i < nums.size(); i++) {
            if (i < n) {
                ans[i >> shift & 1] ^= i;
            }
            ans[nums[i] >> shift & 1] ^= nums[i];
        }
        return ans;
    }
};
