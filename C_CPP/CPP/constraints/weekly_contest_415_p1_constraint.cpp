#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_415_p1.cpp" 

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // 至少需要4个字节才能构造有效输入
    if (size < 4) return false;
    
    // 第一个字节作为n的值，需要满足2 <= n <= 100
    uint8_t n = (data[0] % 99) + 2;
    if (n < 2 || n > 100) return false;
    
    // 检查数据大小是否足够构造nums数组
    if (size < n + 2) return false;
    
    return true;
}

// 检查生成的nums数组是否满足题目要求
bool isValidNums(const vector<int>& nums, int n) {
    // 检查nums长度
    if (nums.size() != n + 2) return false;
    
    // 检查元素范围和重复情况
    vector<int> count(n, 0);
    for (int num : nums) {
        if (num >= n) return false;
        count[num]++;
        if (count[num] > 2) return false;
    }
    
    // 检查是否恰好有两个数重复
    int duplicates = 0;
    for (int c : count) {
        if (c == 2) duplicates++;
    }
    return duplicates == 2;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 构造输入参数
    uint8_t n = (data[0] % 99) + 2;
    vector<int> nums;
    nums.reserve(n + 2);
    
    // 使用后续字节构造nums数组
    for (size_t i = 1; i <= n + 2 && i < size; i++) {
        nums.push_back(data[i] % n);  // 确保元素在[0, n)范围内
    }
    
    // 验证生成的nums是否满足要求
    if (!isValidNums(nums, n)) return 0;

    // TODO: Execute the test function
    Solution solution;
    vector<int> result = solution.getSneakyNumbers(nums);

    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_415_p1/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }

    outFile << "Input: " << "nums = [";
    for (int i = 0; i < nums.size(); i++) {
        outFile << nums[i];
        if (i < nums.size() - 1) outFile << ", ";
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << "[" << result[0] << ", " << result[1] << "]" << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
