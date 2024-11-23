// Problem: Weekly Contest 413 Problem 1
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }

bool checkTwoChessboards(char* coordinate1, char* coordinate2) {
    return (coordinate1[0] - coordinate2[0] + coordinate1[1] - coordinate2[1]) % 2 == 0;
}