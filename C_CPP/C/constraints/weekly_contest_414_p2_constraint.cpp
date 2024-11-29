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
    int maxPossibleScore(int* start, int startSize, int d);
}

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    if (size < 3) return false;  // 至少需要数组长度(1字节)和两个元素(2字节)
    
    size_t len = data[0];
    if (len < 2 || len > 100000) return false;  // 检查数组长度约束
    
    if (size < 1 + len + 1) return false;  // 确保有足够数据构造数组和d
    
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    size_t len = data[0];
    int* start = (int*)malloc(len * sizeof(int));
    if (!start) return 0;
    
    size_t pos = 1;
    for (size_t i = 0; i < len && pos < size - 1; i++) {
        start[i] = data[pos++] % 1000000000;  // 限制在[0, 10^9]范围内
    }
    
    int d = data[pos] % 1000000000;  // 限制在 0 到 10^9 范围内

    // TODO: Execute the test function
    int result = maxPossibleScore(start, len, d);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_414_p2/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "start = [";
    for (size_t i = 0; i < len; i++) {
        outFile << start[i];
        if (i < len - 1) outFile << ", ";
    }
    outFile << "], length = " << len << ", d = " << d << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();

    free(start);
    
    return 0;
}
