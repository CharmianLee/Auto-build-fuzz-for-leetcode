// Problem: Weekly Contest 414 Problem 4
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "weekly_contest_414_p4.h"

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }

// 马的8个可能移动方向
static const int dirs[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, 
                              {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

// 队列操作实现
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) return NULL;
    q->points = (Point*)malloc(sizeof(Point) * capacity);
    if (!q->points) {
        free(q);
        return NULL;
    }
    q->capacity = capacity;
    q->size = 0;
    return q;
}

void freeQueue(Queue* q) {
    if (q) {
        free(q->points);
        free(q);
    }
}

// 计算奇偶性
int getBuildInParity(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count & 1;
}

// DFS函数实现
int dfs(int i, int mask, int n, int positions[][2], int*** dis, int** memo, int u) {
    if (mask == 0) return 0;
    
    if (memo[i][mask] != -1) {
        return memo[i][mask];
    }
    
    int x = positions[i][0], y = positions[i][1];
    int res = -1;
    
    if (getBuildInParity(u ^ mask) == 0) { // Alice's turn
        res = INT_MIN;
        for (int j = 0; j < n; j++) {
            if ((mask >> j) & 1) {
                int temp = dfs(j, mask ^ (1 << j), n, positions, dis, memo, u) + dis[j][x][y];
                res = (res == INT_MIN || temp > res) ? temp : res;
            }
        }
    } else { // Bob's turn
        res = INT_MAX;
        for (int j = 0; j < n; j++) {
            if ((mask >> j) & 1) {
                int temp = dfs(j, mask ^ (1 << j), n, positions, dis, memo, u) + dis[j][x][y];
                res = (temp < res) ? temp : res;
            }
        }
    }
    
    memo[i][mask] = res;
    return res;
}

int maxMoves(int kx, int ky, int** positions, int positionsSize) {
    // 参数验证
    if (!positions || positionsSize < 1 || positionsSize > 15) return -1;
    
    // 分配距离数组 dis[n][50][50]
    int*** dis = (int***)malloc(positionsSize * sizeof(int**));
    if (!dis) return -1;
    
    for (int i = 0; i < positionsSize; i++) {
        dis[i] = (int**)malloc(50 * sizeof(int*));
        if (!dis[i]) {
            // 清理已分配的内存
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < 50; k++) {
                    free(dis[j][k]);
                }
                free(dis[j]);
            }
            free(dis);
            return -1;
        }
        for (int j = 0; j < 50; j++) {
            dis[i][j] = (int*)malloc(50 * sizeof(int));
            if (!dis[i][j]) {
                // 清理已分配的内存
                for (int k = 0; k < j; k++) {
                    free(dis[i][k]);
                }
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < 50; l++) {
                        free(dis[k][l]);
                    }
                    free(dis[k]);
                }
                free(dis);
                return -1;
            }
            memset(dis[i][j], -1, 50 * sizeof(int));
        }
    }
    
    // 计算马到兵的步数
    Queue* q = createQueue(2500); // 50*50最大可能的队列大小
    if (!q) {
        // 清理所有已分配内存
        for (int i = 0; i < positionsSize; i++) {
            for (int j = 0; j < 50; j++) {
                free(dis[i][j]);
            }
            free(dis[i]);
        }
        free(dis);
        return -1;
    }
    
    for (int i = 0; i < positionsSize; i++) {
        int px = positions[i][0], py = positions[i][1];
        dis[i][px][py] = 0;
        
        // 重置队列
        q->size = 0;
        q->points[q->size].x = px;
        q->points[q->size].y = py;
        q->size++;
        
        for (int step = 1; q->size > 0; step++) {
            int currentSize = q->size;
            q->size = 0; // 重置队列大小用于下一层
            
            for (int j = 0; j < currentSize; j++) {
                int qx = q->points[j].x;
                int qy = q->points[j].y;
                
                for (int d = 0; d < 8; d++) {
                    int x = qx + dirs[d][0];
                    int y = qy + dirs[d][1];
                    
                    if (x >= 0 && x < 50 && y >= 0 && y < 50 && dis[i][x][y] == -1) {
                        dis[i][x][y] = step;
                        q->points[q->size].x = x;
                        q->points[q->size].y = y;
                        q->size++;
                    }
                }
            }
        }
    }
    
    freeQueue(q);
    
    // 创建记忆化数组
    int** memo = (int**)malloc((positionsSize + 1) * sizeof(int*));
    if (!memo) {
        // 清理内存
        for (int i = 0; i < positionsSize; i++) {
            for (int j = 0; j < 50; j++) {
                free(dis[i][j]);
            }
            free(dis[i]);
        }
        free(dis);
        return -1;
    }
    
    int maskSize = 1 << positionsSize;
    for (int i = 0; i <= positionsSize; i++) {
        memo[i] = (int*)malloc(maskSize * sizeof(int));
        if (!memo[i]) {
            // 清理内存
            for (int j = 0; j < i; j++) {
                free(memo[j]);
            }
            free(memo);
            for (int j = 0; j < positionsSize; j++) {
                for (int k = 0; k < 50; k++) {
                    free(dis[j][k]);
                }
                free(dis[j]);
            }
            free(dis);
            return -1;
        }
        memset(memo[i], -1, maskSize * sizeof(int));
    }
    
    // 复制positions并添加马的位置
    int (*newPositions)[2] = malloc((positionsSize + 1) * sizeof(*newPositions));
    if (!newPositions) {
        // 清理内存
        for (int i = 0; i <= positionsSize; i++) {
            free(memo[i]);
        }
        free(memo);
        for (int i = 0; i < positionsSize; i++) {
            for (int j = 0; j < 50; j++) {
                free(dis[i][j]);
            }
            free(dis[i]);
        }
        free(dis);
        return -1;
    }
    
    for (int i = 0; i < positionsSize; i++) {
        newPositions[i][0] = positions[i][0];
        newPositions[i][1] = positions[i][1];
    }
    newPositions[positionsSize][0] = kx;
    newPositions[positionsSize][1] = ky;
    
    int u = (1 << positionsSize) - 1;
    int result = dfs(positionsSize, u, positionsSize, newPositions, dis, memo, u);
    
    // 清理所有分配的内存
    free(newPositions);
    for (int i = 0; i <= positionsSize; i++) {
        free(memo[i]);
    }
    free(memo);
    for (int i = 0; i < positionsSize; i++) {
        for (int j = 0; j < 50; j++) {
            free(dis[i][j]);
        }
        free(dis[i]);
    }
    free(dis);
    
    return result;
}