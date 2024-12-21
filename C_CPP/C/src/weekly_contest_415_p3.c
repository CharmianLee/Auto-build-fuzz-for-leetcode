// Problem: Weekly Contest 415 Problem 3
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
int* prefix_function(const char* word, const char* target) {
    char* s = malloc(strlen(word) + strlen(target) + 2);
    strcpy(s, word);
    strcat(s, "#");
    strcat(s, target);
    int n = strlen(s);
    int* pi = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        pi[i] = 0;
    }
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
    free(s);
    return pi;
}

int minValidStrings(char** words, int wordsSize, const char* target) {
    int n = strlen(target);
    int* back = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        back[i] = 0;
    }
    for (int k = 0; k < wordsSize; k++) {
        int* pi = prefix_function(words[k], target);
        int m = strlen(words[k]);
        for (int i = 0; i < n; i++) {
            if (pi[m + 1 + i] > back[i]) {
                back[i] = pi[m + 1 + i];
            }
        }
        free(pi);
    }

    int* dp = (int*)malloc(sizeof(int) * (n + 1));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1000000000;
    }
    for (int i = 0; i < n; i++) {
        dp[i + 1] = dp[i + 1 - back[i]] + 1;
        if (dp[i + 1] > n) {
            break;
        }
    }
    int res = dp[n];
    free(back);
    free(dp);
    return res;
}