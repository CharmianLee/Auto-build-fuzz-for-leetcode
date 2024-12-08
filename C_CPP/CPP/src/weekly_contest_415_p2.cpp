// Problem: Weekly Contest 415 Problem 2
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<array<long long, 4>> memo(n);
        for (auto& row : memo) {
            fill(row.begin(), row.end(), LLONG_MIN); // 表示没有计算过
        }

        auto dfs = [&](auto&& dfs, int i, int j) -> long long {
            if (j < 0) { // 选完了
                return 0;
            }
            if (i < 0) { // j >= 0，没选完
                return LLONG_MIN / 2; // 防止溢出
            }
            auto& res = memo[i][j]; // 注意这里是引用
            if (res == LLONG_MIN) { // 需要计算，并记忆化
                res = max(dfs(dfs, i - 1, j), dfs(dfs, i - 1, j - 1) + (long long) a[j] * b[i]);
            }
            return res;
        };

        return dfs(dfs, n - 1, 3);
    }
};
