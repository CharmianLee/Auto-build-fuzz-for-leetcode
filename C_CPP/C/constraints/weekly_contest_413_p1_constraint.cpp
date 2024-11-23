#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <filesystem>
#include <fstream>

extern "C" {
    // TODO: Add your function declaration here
    // Example: bool solutionFunction(type1 param1, type2 param2);
    bool checkTwoChessboards(char* coordinate1, char* coordinate2);
}

// Add your input validation functions here
bool isValidCoordinate(const char* coord) {
    if (strlen(coord) != 2) return false;
    if (coord[0] < 'a' || coord[0] > 'h') return false;
    if (coord[1] < '1' || coord[1] > '8') return false;
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    // 确保输入长度足够表示两个坐标
    if (size < 4) return 0;  // Basic size check
    
    // TODO: Transform fuzzer input into valid function parameters
    // 创建两个坐标字符串
    char coordinate1[3] = {0};
    char coordinate2[3] = {0};

    // 从fuzzer输入数据构造坐标
    coordinate1[0] = 'a' + (data[0] % 8);  // 确保在a-h范围内
    coordinate1[1] = '1' + (data[1] % 8);  // 确保在1-8范围内
    coordinate2[0] = 'a' + (data[2] % 8);
    coordinate2[1] = '1' + (data[3] % 8);

    // 验证坐标格式
    if (!isValidCoordinate(coordinate1) || !isValidCoordinate(coordinate2)) {
        return 0;
    }

    // TODO: Execute the test function
    bool result = checkTwoChessboards(coordinate1, coordinate2);
    
    // Save test case
    std::string outputDir = "/home/charmian/Code/leetcode_fuzz_test/fuzz_outputs/C/weekly_contest_413_p1/output/";
    std::ofstream outFile;
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << coordinate1 << " " << coordinate2 << std::endl;
    outFile << "Output: " << (result ? "true" : "false") << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
