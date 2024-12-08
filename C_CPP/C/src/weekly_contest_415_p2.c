// Problem: Weekly Contest 415 Problem 2
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
long long maxScore(int* a, int aSize, int* b, int bSize) {
    // 定义数组b的长度
    int n = bSize;
    // 定义二维数组f，用于存储每个状态下的最大得分
    long long f[bSize + 1][5];
    // 初始化数组f，所有元素都为INT_MIN
    for(int i = 0; i <= bSize; i++) {
        for(int j = 0; j <= 4; j++) {
            f[i][j] = INT_MIN;
        }
    }
    // 初始化f[0][0]为0，表示初始状态下的得分为0
    f[0][0] = 0;
    // 遍历数组b，计算每个状态下的最大得分
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= 4; j++) {
            // 如果当前状态下的得分为f[i-1][j]，则更新f[i][j]
            f[i][j] = f[i-1][j];
            // 如果当前状态下的得分大于0，则更新f[i][j]
            if(j > 0) {
                f[i][j] = fmax(f[i][j], f[i-1][j-1] + 1LL * a[j-1] * b[i-1]);
            }
        }
    }
    // 返回数组b的最后一个状态下的最大得分
    return f[n][4];
}