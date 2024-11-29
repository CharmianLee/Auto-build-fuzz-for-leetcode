#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_414_p2.cpp" 

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // 确保有足够的数据来构造测试用例
    // 至少需要3个字节：1个字节表示数组长度，2个字节作为最小数据
    if (size < 3) return false;
    
    // 获取数组长度（使用第一个字节）
    size_t len = data[0];
    
    // 验证数组长度是否在题目约束范围内 (2 <= start.length <= 10^5)
    if (len < 2 || len > 100000) return false;
    
    // 确保有足够的数据来构造数组和d值
    // 每个数组元素需要至少1个字节，d值需要1个字节
    if (size < 1 + len + 1) return false;
    
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 从fuzzer输入构造测试参数
    size_t len = data[0];  // 使用第一个字节作为数组长度
    vector<int> start;
    size_t pos = 1;

    // 构造start数组
    for (size_t i = 0; i < len && pos < size - 1; i++) {
        // 使用剩余字节构造数组元素（对大数取模以符合约束）
        int value = data[pos++] % 1000000000;  // 限制在 0 到 10^9 范围内
        start.push_back(value);
    }
    
    // 构造d参数（使用最后一个字节，同样取模以符合约束）
    int d = data[pos] % 1000000000;  // 限制在 0 到 10^9 范围内
    
    // TODO: Execute the test function
    Solution solution;
    int result = solution.maxPossibleScore(start, d);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_414_p2/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "start = [";
    for (size_t i = 0; i < start.size(); i++) {
        outFile << start[i];
        if (i < start.size() - 1) {
            outFile << ", ";
        }
    }
    outFile << "], d = " << d << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
