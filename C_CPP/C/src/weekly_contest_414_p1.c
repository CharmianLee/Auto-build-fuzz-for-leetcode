// Problem: Weekly Contest 414 Problem 1
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {
//     // Implementation
// }
// convertDateToBinary函数的声明
// 使用GPT-o1生成的代码
char* convertDateToBinary(char* date) {
    char * ans = (char *)calloc(25, sizeof(char)); // 分配25个字符的空间
    char * ptr = ans + 24; // 指向分配空间的最后一个位置

    // 转换日
    int d = atoi(date + 8);
    if (d == 0) {
        *--ptr = '0';
    } else {
        while (d) {
            *--ptr = (d & 1) + '0';
            d >>= 1;
        }
    }
    *--ptr = '-';

    // 转换月
    int m = atoi(date + 5);
    if (m == 0) {
        *--ptr = '0';
    } else {
        while (m) {
            *--ptr = (m & 1) + '0';
            m >>= 1;
        }
    }
    *--ptr = '-';

    // 转换年
    int y = atoi(date);
    if (y == 0) {
        *--ptr = '0';
    } else {
        while (y) {
            *--ptr = (y & 1) + '0';
            y >>= 1;
        }
    }

    // 将结果移至 ans 的开头
    size_t len = ans + 25 - ptr; // 修改为25，包含字符串结束符的位置
    memmove(ans, ptr, len);
    ans[len] = '\0'; // 添加字符串结束符

    return ans;
}