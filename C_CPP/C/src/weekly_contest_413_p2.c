// Problem: Weekly Contest 413 Problem 2
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
int* resultsArray(int** queries, int queriesSize, int* queriesColSize, int k, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * queriesSize);
    *returnSize = queriesSize;
    memset(result, -1, sizeof(int) * queriesSize);
    
    // 使用数组模拟优先队列，保持数组有序
    int* distanceArr = (int*)malloc(sizeof(int) * (k + 1));
    int distanceSize = 0;
    
    for (int i = 0; i < queriesSize; i++) {
        int distance = abs(queries[i][0]) + abs(queries[i][1]);
        
        // 插入新距离并保持有序（从大到小）
        int j = distanceSize;
        while (j > 0 && distanceArr[j - 1] < distance) {
            if (j < k) {
                distanceArr[j] = distanceArr[j - 1];
            }
            j--;
        }
        if (j < k) {
            distanceArr[j] = distance;
            if (distanceSize < k) distanceSize++;
        }
        
        // 如果已经收集了k个距离，取第k个（即最小的）作为结果
        if (distanceSize == k) {
            result[i] = distanceArr[k - 1];
        }
    }
    
    free(distanceArr);
    return result;
}
