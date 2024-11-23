// Problem: Weekly Contest 413 Problem 1
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }

    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        return (coordinate1[0] - coordinate2[0] + coordinate1[1] - coordinate2[1]) % 2 == 0;
    }
};
