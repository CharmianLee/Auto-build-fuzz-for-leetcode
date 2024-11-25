// Problem: Weekly Contest 413 Problem 4
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
int* maximumSubarrayXor(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int** subarrayXors = (int**) malloc(sizeof(int*) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        subarrayXors[i] = (int*) malloc(sizeof(int) * numsSize);
        memset(subarrayXors[i], 0, sizeof(int) * numsSize);
        subarrayXors[i][i] = nums[i];
    }
    for (int i = 0; i < numsSize; i++) {
        subarrayXors[i][i] = nums[i];
    }
    for (int subLength = 2; subLength <= numsSize; subLength++) {
        for (int i = 0, j = subLength - 1; j < numsSize; i++, j++) {
            subarrayXors[i][j] = subarrayXors[i][j - 1] ^ subarrayXors[i + 1][j];
        }
    }
    int** maxScores = (int**) malloc(sizeof(int*) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        maxScores[i] = (int*) malloc(sizeof(int) * numsSize);
        memset(maxScores[i], 0, sizeof(int) * numsSize);
        maxScores[i][i] = nums[i];
    }
    for (int subLength = 2; subLength <= numsSize; subLength++) {
        for (int i = 0, j = subLength - 1; j < numsSize; i++, j++) {
            maxScores[i][j] = fmax(subarrayXors[i][j], fmax(maxScores[i][j - 1], maxScores[i + 1][j]));
        }
    }
    int* answer = (int*) malloc(sizeof(int) * queriesSize);
    for (int i = 0; i < queriesSize; i++) {
        answer[i] = maxScores[queries[i][0]][queries[i][1]];
    }
    *returnSize = queriesSize;
    
    // Free allocated memory
    for (int i = 0; i < numsSize; i++) {
        free(subarrayXors[i]);
        free(maxScores[i]);
    }
    free(subarrayXors);
    free(maxScores);
    
    return answer;
}
