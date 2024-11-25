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
    int maxScore(int** grid, int gridSize, int* gridColSize);
}

// Add your input validation functions here
// 输入验证函数
bool isValidInput(const uint8_t* data, size_t size) {
    // 检查输入数据大小是否足够包含基本信息
    // 需要至少3个字节：行数、列数和至少一个元素
    if (size < 3) return false;
    
    // 获取行数和列数
    uint8_t rows = data[0] % 10 + 1;  // 确保 1 <= rows <= 10
    uint8_t cols = data[1] % 10 + 1;  // 确保 1 <= cols <= 10
    
    // 检查是否有足够的数据来填充网格
    size_t required_size = 2 + (rows * cols);
    return size >= required_size;
}

// 从模糊测试输入数据构建网格
void buildGrid(const uint8_t* data, size_t size, int*** grid, int* gridSize, int** gridColSize) {
    *gridSize = data[0] % 10 + 1;  // 行数
    int cols = data[1] % 10 + 1;   // 列数
    
    // 分配网格内存
    *grid = (int**)malloc((*gridSize) * sizeof(int*));
    *gridColSize = (int*)malloc((*gridSize) * sizeof(int));
    
    for(int i = 0; i < *gridSize; i++) {
        (*grid)[i] = (int*)malloc(cols * sizeof(int));
        (*gridColSize)[i] = cols;
    }
    
    // 填充网格数据
    size_t idx = 2;
    for(int i = 0; i < *gridSize; i++) {
        for(int j = 0; j < cols; j++) {
            // 确保元素在 1 到 100 的范围内
            (*grid)[i][j] = (data[idx++] % 100) + 1;
        }
    }
}

// 释放网格内存
void freeGrid(int** grid, int gridSize) {
    for(int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(grid);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 构建测试用例
    int** grid;
    int gridSize;
    int* gridColSize;
    buildGrid(data, size, &grid, &gridSize, &gridColSize);

    // TODO: Execute the test function
    int result = maxScore(grid, gridSize, gridColSize);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_413_p3/output/";
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
    for(int i = 0; i < gridSize; i++) {
        outFile << "[";
        for(int j = 0; j < gridColSize[i]; j++) {
            outFile << grid[i][j];
            if(j < gridColSize[i] - 1) outFile << ",";
        }
        if (i < gridSize - 1) outFile << "],";
        else outFile << "]";
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    // 释放内存
    freeGrid(grid, gridSize);
    free(gridColSize);
    
    return 0;
}
