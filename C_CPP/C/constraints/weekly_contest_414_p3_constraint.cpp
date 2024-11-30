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
    long long findMaximumScore(int* nums, int numsSize);
}

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    if (size < sizeof(uint32_t)) return false;
    
    uint32_t numsSize = *(uint32_t*)data;
    if (numsSize < 1 || numsSize > 100000) return false;
    
    if (size < sizeof(uint32_t) + numsSize * sizeof(int)) return false;
    
    const int* nums = (int*)(data + sizeof(uint32_t));
    for (uint32_t i = 0; i < numsSize; i++) {
        if (nums[i] < 1 || nums[i] > 100000) return false;
    }
    
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    uint32_t numsSize = *(uint32_t*)data;
    const int* nums_data = (int*)(data + sizeof(uint32_t));
    
    int* nums = (int*)malloc(numsSize * sizeof(int));
    memcpy(nums, nums_data, numsSize * sizeof(int));

    // TODO: Execute the test function
    long long result = findMaximumScore(nums, numsSize);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_414_p3/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "nums = [";
    for (uint32_t i = 0; i < numsSize; i++) {
        outFile << nums[i];
        if (i < numsSize - 1) outFile << ", ";
    }
    outFile << "] , numsSize = " << numsSize << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();

    free(nums);
    
    return 0;
}
