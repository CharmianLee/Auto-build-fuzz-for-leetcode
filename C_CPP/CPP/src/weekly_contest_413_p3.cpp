// Problem: Weekly Contest 413 Problem 3
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }
    int maxScore(vector<vector<int>>& grid) {
        unordered_map<int, int> pos;
        int m = grid.size();
        for (int i = 0; i < m; i++) {
            for (int x : grid[i]) {
                pos[x] |= 1 << i;
            }
        }

        vector<int> all_nums;
        for (auto& [x, _] : pos) {
            all_nums.push_back(x);
        }

        int n = all_nums.size();
        vector<vector<int>> memo(n, vector<int>(1 << m, -1));
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (i < 0) {
                return 0;
            }
            int& res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = dfs(dfs, i - 1, j);
            int x = all_nums[i];
            for (int t = pos[x], lb; t; t ^= lb) {
                lb = t & -t;
                if ((j & lb) == 0) {
                    res = max(res, dfs(dfs, i - 1, j | lb) + x);
                }
            }
            return res;
        };
        return dfs(dfs, n - 1, 0);
    }
};
