#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_415_p2.cpp" 

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // 需要至少21字节：16字节用于a数组(4个int)，1字节用于b长度，至少4个字节用于b数组
    if (size < 21) return false;
    
    // 检查b的长度
    uint32_t bLen;
    memcpy(&bLen, data + 16, sizeof(uint32_t));  // 第17-20个字节存储b的长度
    bLen = 4 + (bLen % (100000 - 4 + 1));       // 限制bLen在[4, 100000]
    
    // 检查数据大小是否足够包含 b 数组
    if (size < 20 + bLen * 4) return false;
    
    return true;
}

bool isValidValue(int value) {
    return value >= -100000 && value <= 100000;
}

// 从字节数据构造int
int bytesToInt(const uint8_t* bytes) {
    int value = 0;
    memcpy(&value, bytes, sizeof(int));
    value = std::max(-100000, std::min(100000, value)); // 限制在[-10^5, 10^5]范围内
    return value;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 构造 a 数组
    vector<int> a;
    a.reserve(4);
    for (size_t i = 0; i < 4; i++) {
        int value;
        memcpy(&value, data + i * 4, sizeof(int));
        value = std::max(-100000, std::min(100000, value)); // 限制在 [-1e5, 1e5]
        a.push_back(value);
    }

    // 获取 b 的长度 bLen
    uint32_t bLen;
    memcpy(&bLen, data + 16, sizeof(uint32_t));
    bLen = 4 + (bLen % (100000 - 4 + 1)); // 限制 bLen 在 [4, 100000]

    // 检查数据大小是否足够包含 b 数组
    if (size < 20 + bLen * 4) return 0;

    // 构造 b 数组
    vector<int> b;
    b.reserve(bLen);
    for (size_t i = 0; i < bLen; i++) {
        size_t index = 20 + i * 4;
        int value;
        memcpy(&value, data + index, sizeof(int));
        value = std::max(-100000, std::min(100000, value)); // 限制在 [-1e5, 1e5]
        b.push_back(value);
    }

    // TODO: Execute the test function
    Solution solution;
    long long result = solution.maxScore(a, b);

    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_415_p2/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "a = [" << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << "], b = [";
    for (size_t i = 0; i < b.size(); i++) {
        outFile << b[i];
        if (i < b.size() - 1) outFile << ", ";
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
