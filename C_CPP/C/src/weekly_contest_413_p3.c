// Problem: Weekly Contest 413 Problem 3
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
// weekly_contest_413_p3.c

int maxScore(int** grid, int gridSize, int* gridColSize) {
    int ans = 0;
    int maxnum = 0;
    int m = gridSize;
    int n = gridColSize[0];
    for(int i = 0;i < m;i++){
        for(int j = 0; j < n;j++){
            maxnum = fmax(maxnum, grid[i][j]);
        }
    }
    int numsRaw[maxnum + 1];
    memset(numsRaw, 0, sizeof(numsRaw));
    for(int i = 0; i < m;i++){
        for(int j = 0; j< n;j++){
            numsRaw[grid[i][j]] |= 1 << i;
        }
    }
    int dp[maxnum+1][1 << m + 1];
    for(int i = 0; i < maxnum + 1;i++){
        for(int j = 0 ;j < 1<<m+1;j++){
            dp[i][j] = INT_MIN;
        }
    }
    dp[0][0] = 0;
    for(int i = 1; i <= maxnum;i++){
        for(int j = 0; j < (1 << m);j++){
            dp[i][j] = fmax(dp[i][j], dp[i-1][j]);
            //选第k行元素
            for(int k = 0; k < m; k++){
                if((numsRaw[i] >> k & 1) && (j >> k & 1)){
                    dp[i][j] = fmax(dp[i][j], dp[i-1][j ^ (1 << k)] + i);
                    ans = fmax(ans, dp[i][j]);
                }
            }
        }
    }
    return ans;
}