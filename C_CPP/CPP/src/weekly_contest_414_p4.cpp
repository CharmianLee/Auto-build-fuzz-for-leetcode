// Problem: Weekly Contest 414 Problem 4
#include <string>
#include <vector>
#include <climits>
#include <string.h>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }
    static constexpr int dirs[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        int n = positions.size();
        int dis[n][50][50];
        memset(dis, -1, sizeof(dis));
        // Calculate steps from knight to pawns
        for (int i = 0; i < n; i++) {
            int px = positions[i][0], py = positions[i][1];
            dis[i][px][py] = 0;
            vector<pair<int, int>> q = {{px, py}};
            for (int step = 1; !q.empty(); step++) {
                vector<pair<int, int>> tmp;
                for (auto& [qx, qy] : q) {
                    for (auto& [dx, dy] : dirs) {
                        int x = qx + dx, y = qy + dy;
                        if (0 <= x && x < 50 && 0 <= y && y < 50 && dis[i][x][y] < 0) {
                            dis[i][x][y] = step;
                            tmp.emplace_back(x, y);
                        }
                    }
                }
                q = move(tmp);
            }
        }

        positions.push_back({kx, ky});
        vector<vector<int>> memo(n + 1, vector<int>(1 << n, -1));
        int u = (1 << n) - 1;
        auto dfs = [&](auto&& dfs, int i, int mask) -> int {
            if (mask == 0) return 0;
            int& res = memo[i][mask];
            if (res != -1) return res;
            
            int x = positions[i][0], y = positions[i][1];
            if (__builtin_parity(u ^ mask) == 0) {
                for (int j = 0; j < n; j++) {
                    if (mask >> j & 1) {
                        res = max(res, dfs(dfs, j, mask ^ (1 << j)) + dis[j][x][y]);
                    }
                }
            } else {
                res = INT_MAX;
                for (int j = 0; j < n; j++) {
                    if (mask >> j & 1) {
                        res = min(res, dfs(dfs, j, mask ^ (1 << j)) + dis[j][x][y]);
                    }
                }
            }
            return res;
        };
        return dfs(dfs, n, u);
    }
};
