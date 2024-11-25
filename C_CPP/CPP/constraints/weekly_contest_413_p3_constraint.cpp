#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../src/weekly_contest_413_p3.cpp"

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // 检查输入数据大小是否足够生成有效的网格
    // 至少需要 3 个字节：行数、列数和至少一个元素
    if (size < 3) return false;
    
    // 获取行数和列数
    uint8_t rows = data[0] % 10 + 1;  // 确保 1 <= rows <= 10
    uint8_t cols = data[1] % 10 + 1;  // 确保 1 <= cols <= 10
    
    // 检查是否有足够的数据来填充网格
    size_t required_size = 2 + (rows * cols);
    return size >= required_size;
}

// 从模糊测试输入数据构建网格
vector<vector<int>> buildGrid(const uint8_t* data, size_t size) {
    uint8_t rows = data[0] % 10 + 1;
    uint8_t cols = data[1] % 10 + 1;
    
    vector<vector<int>> grid(rows, vector<int>(cols));
    size_t idx = 2;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // 确保元素在 1 到 100 的范围内
            grid[i][j] = (data[idx++] % 100) + 1;
        }
    }
    
    return grid;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 构建测试用例
    vector<vector<int>> grid = buildGrid(data, size);

    // TODO: Execute the test function
    Solution solution;
    int result = solution.maxScore(grid);

    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_413_p3/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }

    // 格式化输入输出
    outFile << "Input: Grid = [";
    for (const auto& row : grid) {
        outFile << "[";
        for (size_t i = 0; i < row.size(); i++) {
            outFile << row[i];
            if (i < row.size() - 1) outFile << ",";
        }
        if (&row != &grid.back()) outFile << "],";
        else outFile << "]";
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
