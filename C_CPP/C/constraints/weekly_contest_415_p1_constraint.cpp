#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

extern "C" {
    // TODO: Add your function declaration here
    // Example: bool solutionFunction(type1 param1, type2 param2);
    int* getSneakyNumbers(int* nums, int numsSize, int* returnSize);
}

// Add your input validation functions here
// 检查数字在数组中出现的次数
int countOccurrences(const int* nums, int numsSize, int target) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == target) count++;
    }
    return count;
}

bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // 至少需要4个字节才能构造有效输入
    if (size < 4) return false;
    
    // 第一个字节作为n的值，需要满足2 <= n <= 100
    uint8_t n = (data[0] % 99) + 2;
    if (n < 2 || n > 100) return false;
    
    // 检查数据大小是否足够构造nums数组
    if (size < n + 3) return false;
    
    return true;
}

// 检查生成的nums数组是否满足题目要求
bool isValidNums(const int* nums, int numsSize, int n) {
    // 检查nums长度
    if (numsSize != n + 2) return false;
    
    // 检查元素范围和重复情况
    int duplicates = 0;
    bool* seen = (bool*)calloc(n, sizeof(bool));
    if (!seen) return false;
    
    for (int i = 0; i < numsSize; i++) {
        // 检查元素范围
        if (nums[i] >= n) {
            free(seen);
            return false;
        }
        
        // 检查重复情况
        int count = countOccurrences(nums, numsSize, nums[i]);
        if (count > 2) {
            free(seen);
            return false;
        }
        if (count == 2 && !seen[nums[i]]) {
            duplicates++;
            seen[nums[i]] = true;
        }
    }
    
    free(seen);
    return duplicates == 2;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 构造输入参数
    uint8_t n = (data[0] % 99) + 2;
    int numsSize = n + 2;
    int* nums = (int*)malloc(numsSize * sizeof(int));
    if (!nums) return 0;
    
    // 使用后续字节构造nums数组
    for (int i = 0; i < numsSize && i + 1 < size; i++) {
        nums[i] = data[i + 1] % n;  // 确保元素在[0, n)范围内
    }
    
    // 验证生成的nums是否满足要求
    if (!isValidNums(nums, numsSize, n)) {
        free(nums);
        return 0;
    }

    // TODO: Execute the test function
    int returnSize;
    int* result = getSneakyNumbers(nums, numsSize, &returnSize);

    // 验证输出结果
    bool validOutput = true;
    if (returnSize != 2) validOutput = false;
    if (result[0] == result[1]) validOutput = false;
    if (countOccurrences(nums, numsSize, result[0]) != 2 || 
        countOccurrences(nums, numsSize, result[1]) != 2) {
        validOutput = false;
    }

    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_415_p1/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "nums = [";
    for (int i = 0; i < numsSize; i++) {
        outFile << nums[i];
        if (i < numsSize - 1) outFile << ", ";
    }
    outFile << "]" << std::endl;
    if (validOutput) {
        outFile << "Output: " << "[" << result[0] << ", " << result[1] << "]" << std::endl;
    } else {
        outFile << "Output: " << "Invalid output" << std::endl;
    }
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    free(nums);
    free(result);

    return 0;
}
