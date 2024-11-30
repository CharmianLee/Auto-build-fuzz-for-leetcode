// weekly_contest_414_p4.h

#ifndef WEEKLY_CONTEST_414_P4_H
#define WEEKLY_CONTEST_414_P4_H

#ifdef __cplusplus
extern "C" {
#endif

// 头文件的其他内容
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 坐标点结构
typedef struct {
    int x;
    int y;
} Point;

// 队列结构
typedef struct {
    Point* points;
    int capacity;
    int size;
} Queue;

// 函数声明
Queue* createQueue(int capacity);
void freeQueue(Queue* q);
int getBuildInParity(int n);
int dfs(int i, int mask, int n, int positions[][2], int*** dis, int** memo, int u);
int maxMoves(int kx, int ky, int** positions, int positionsSize);

#ifdef __cplusplus
}
#endif

#endif // WEEKLY_CONTEST_414_P4_H