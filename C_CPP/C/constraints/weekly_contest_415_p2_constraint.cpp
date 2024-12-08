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
    long long maxScore(int* a, int aSize, int* b, int bSize);
}

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // 需要至少21字节：16字节用于a数组(4个int)，1字节用于b长度，至少4个字节用于b数组
    if (size < 21) return false;
    
    // 检查b的长度
    uint32_t bLen;
    memcpy(&bLen, data + 16, sizeof(uint32_t));  // 第17-20个字节存储b的长度
    bLen = 4 + (bLen % (100000 - 4 + 1));       // 限制bLen在[4, 100000]
    
    // 检查数据大小是否足够包含 b 数组
    if (size < 20 + bLen * 4) return false;
    
    // 检查数据大小是否足够
    if (size < 17 + bLen * 4) return false;
    
    return true;
}

// 检查数值是否在有效范围内
bool isValidValue(int value) {
    return value >= -100000 && value <= 100000;
}

// 从字节数据构造int，并确保在有效范围内
int bytesToInt(const uint8_t* bytes) {
    int value;
    memcpy(&value, bytes, sizeof(int));
    if (value < -100000) value = -100000;
    if (value > 100000) value = 100000;
    return value;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 构造a数组
    int* a = (int*)malloc(4 * sizeof(int));
    if (!a) return 0;
    
    for (int i = 0; i < 4; i++) {
        a[i] = bytesToInt(data + i * 4);
    }
    
    // 获取 b 的长度 bLen
    uint32_t bLen;
    memcpy(&bLen, data + 16, sizeof(uint32_t));
    bLen = 4 + (bLen % (100000 - 4 + 1));  // 限制 bLen 在 [4, 100000]
    
    // 检查数据大小是否足够包含 b 数组
    if (size < 20 + bLen * 4) {
        free(a);
        return 0;
    }

    // 构造b数组
    int* b = (int*)malloc(bLen * sizeof(int));
    if (!b) {
        free(a);
        return 0;
    }
    
    for (uint32_t i = 0; i < bLen; i++) {
        b[i] = bytesToInt(data + 20 + i * 4);
    }

    // TODO: Execute the test function
    long long result = maxScore(a, 4, b, bLen);

    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_415_p2/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "a = [" << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << "], b = [";
    for (int i = 0; i < bLen; i++) {
        outFile << b[i];
        if (i < bLen - 1) outFile << ", ";
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();

    free(a);
    free(b);
    
    return 0;
}
