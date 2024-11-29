// Problem: Weekly Contest 414 Problem 2
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <ranges>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }
    int maxPossibleScore(vector<int>& start, int d) {
        sort(start.begin(), start.end());

        auto check = [&](int score) -> bool {
            long long x = LLONG_MIN;
            for (int s : start) {
                x = max(x + score, (long long)s);
                if (x > s + d) {
                    return false;
                }
            }
            return true;
        };

        int left = 0, right = (start.back() + d - start[0]) / (start.size() - 1) + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};
