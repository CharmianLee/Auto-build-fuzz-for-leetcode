#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_414_p3.cpp" 

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // 确保至少有足够的数据来表示数组长度
    if (size < sizeof(uint32_t)) return false;
    
    // 获取数组长度
    uint32_t length = *(uint32_t*)data;
    
    // 验证数组长度是否在题目约束范围内 (1 <= nums.length <= 10^5)
    if (length < 1 || length > 100000) return false;
    
    // 确保有足够的数据来表示所有数组元素
    if (size < sizeof(uint32_t) + length * sizeof(uint32_t)) return false;
    
    // 验证每个数组元素是否在题目约束范围内 (1 <= nums[i] <= 10^5)
    const uint32_t* nums = (uint32_t*)(data + sizeof(uint32_t));
    for (uint32_t i = 0; i < length; i++) {
        if (nums[i] < 1 || nums[i] > 100000) return false;
    }
    
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 将fuzzer输入转换为函数参数
    uint32_t length = *(uint32_t*)data;
    const uint32_t* nums_data = (uint32_t*)(data + sizeof(uint32_t));
    
    // 构造输入vector
    vector<int> nums;
    for (uint32_t i = 0; i < length; i++) {
        nums.push_back(nums_data[i]);
    }

    // TODO: Execute the test function
    Solution solution;
    long long result = solution.findMaximumScore(nums);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_414_p3/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "nums = [";
    for (uint32_t i = 0; i < length; i++) {
        outFile << nums_data[i];
        if (i < length - 1) outFile << ", ";
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
