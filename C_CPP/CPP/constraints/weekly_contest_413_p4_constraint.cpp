#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_413_p4.cpp" 

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // 检查基本大小要求
    if (size < sizeof(int) * 2) return false; // 至少需要numsSize和queriesSize
    
    // 获取数组大小
    int numsSize = *(int*)data;
    if (numsSize < 1 || numsSize > 2000) return false;
    
    // 计算queries数组大小
    int queriesSize = *(int*)(data + sizeof(int));
    if (queriesSize < 1 || queriesSize > 100000) return false;
    
    // 检查总大小是否足够
    size_t requiredSize = sizeof(int) * 2 + // numsSize和queriesSize
                         sizeof(int) * numsSize + // nums数组
                         sizeof(int) * 2 * queriesSize; // queries二维数组
    
    return size >= requiredSize;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // Extract array sizes
    uint32_t n = *(uint32_t*)data;
    uint32_t q = *(uint32_t*)(data + 4);
    
    // Create nums array
    vector<int> nums;
    const int* nums_data = (const int*)(data + 8);
    for (uint32_t i = 0; i < n && i < (size - 8) / sizeof(int); i++) {
        nums.push_back(nums_data[i] & ((1U << 31) - 1)); // Ensure nums[i] <= 2^31 - 1
    }
    
    // Create queries array
    vector<vector<int>> queries;
    const int* queries_data = nums_data + n;
    for (uint32_t i = 0; i < q && i < (size - 8 - n * sizeof(int)) / (2 * sizeof(int)); i++) {
        int l = queries_data[2 * i] % n;     // Ensure 0 <= l < n
        int r = queries_data[2 * i + 1] % n; // Ensure 0 <= r < n
        if (l > r) swap(l, r);              // Ensure l <= r
        queries.push_back({l, r});
    }

    // TODO: Execute the test function
    Solution solution;
    vector<int> result = solution.maximumSubarrayXor(nums, queries);

    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_413_p4/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }

    outFile << "Input: nums = [";
    for (size_t i = 0; i < nums.size(); i++)
    {
        outFile << nums[i];
        if (i < nums.size() - 1)
            outFile << ",";
    }
    outFile << "],";

    outFile << " queries = [";
    for (size_t i = 0; i < queries.size(); i++)
    {
        outFile << "[" << queries[i][0] << "," << queries[i][1] << "]";
        if (i < queries.size() - 1)
            outFile << ",";
    }
    outFile << "]\n";

    outFile << "Output: [";
    for (size_t i = 0; i < result.size(); i++)
    {
        outFile << result[i];
        if (i < result.size() - 1)
            outFile << ",";
    }
    outFile << "]\n";
    outFile << "--------------------------\n";
    outFile.close();

    return 0;
}
