// Problem: Weekly Contest 415 Problem 3
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
    int minValidStrings(vector<string>& words, string target) {
        auto prefix_function = [](const string& word, const string& target) -> vector<int> {
            string s = word + '#' + target;
            int n = s.size();
            vector<int> pi(n, 0);
            for (int i = 1; i < n; i++) {
                int j = pi[i - 1];
                while (j > 0 && s[i] != s[j]) {
                    j = pi[j - 1];
                }
                if (s[i] == s[j]) {
                    j++;
                }
                pi[i] = j;
            }
            return pi;
        };

        int n = target.size();
        vector<int> back(n, 0);
        for (const string& word : words) {
            vector<int> pi = prefix_function(word, target);
            int m = word.size();
            for (int i = 0; i < n; i++) {
                if (m + 1 + i < pi.size()) {
                    back[i] = max(back[i], pi[m + 1 + i]);
                }
            }
        }

        // Initialize DP array with a large number
        const int INF = 1e9;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            if (dp[i] == INF) continue; // Skip if current position is unreachable
            int max_back = back[i];
            if (max_back == 0) continue; // No valid prefix ends here
            if (i + max_back > n) max_back = n - i;
            dp[i + max_back] = min(dp[i + max_back], dp[i] + 1);
        }

        return dp[n] == INF ? -1 : dp[n];
    }
};
