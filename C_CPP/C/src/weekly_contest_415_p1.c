// Problem: Weekly Contest 415 Problem 1
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
int* getSneakyNumbers(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)calloc(2, sizeof(int));
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] == nums[j]) {
                result[count] = nums[i];
                count++;
                break;
            }
        }
        if (count == 2)
            break;
    }
    *returnSize=2;
    return result;
}