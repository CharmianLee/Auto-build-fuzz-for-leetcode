// Problem: Weekly Contest 414 Problem 3
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
long long findMaximumScore(int* nums, int numsSize) {
    long long ans = 0LL, l = 0LL, r = 1LL;
    for (; r < numsSize; ++r)
        if (nums[l] < nums[r]) 
            ans += (r - l) * nums[l], l = r;
    return ans + (r - l - 1) * nums[l];
}
