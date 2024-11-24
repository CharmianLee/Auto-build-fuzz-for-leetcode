// Problem: Weekly Contest 413 Problem 2
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        vector<int> ans(queries.size(), -1);
        priority_queue<int> pq;
        for (int i = 0; i < queries.size(); i++) {
            pq.push(abs(queries[i][0]) + abs(queries[i][1]));
            if (pq.size() > k) {
                pq.pop();
            }
            if (pq.size() == k) {
                ans[i] = pq.top();
            }
        }
        return ans;
    }
};
