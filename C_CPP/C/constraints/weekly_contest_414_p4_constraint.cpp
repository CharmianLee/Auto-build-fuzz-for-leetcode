#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../src/weekly_contest_414_p4.h"

extern "C" {
    // TODO: Add your function declaration here
    // Example: bool solutionFunction(type1 param1, type2 param2);
    #include "../src/weekly_contest_414_p4.h"
}

// Add your input validation functions here
bool isValidPosition(int x, int y) {
    return x >= 0 && x <= 49 && y >= 0 && y <= 49;
}

bool isValidPositionsSize(int size) {
    return size >= 1 && size <= 15;
}

bool arePositionsUnique(int** positions, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (positions[i][0] == positions[j][0] && 
                positions[i][1] == positions[j][1]) {
                return false;
            }
        }
    }
    return true;
}

bool isKnightPositionValid(int kx, int ky, int** positions, int size) {
    for (int i = 0; i < size; i++) {
        if (positions[i][0] == kx && positions[i][1] == ky) {
            return false;
        }
    }
    return true;
}

bool isValidInput(const uint8_t* data, size_t size) {
    if (size < 5) return false;

    int kx = data[0];
    int ky = data[1];
    int positions_count = (data[2] % 15) + 1; // 修改这里

    if (size < 3 + positions_count * 2) return false;
    if (!isValidPosition(kx, ky)) return false;
    if (!isValidPositionsSize(positions_count)) return false;

    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    int kx = data[0] % 50;
    int ky = data[1] % 50;
    int positions_count = (data[2] % 15) + 1;
    
    // 分配内存
    int** positions = (int**)malloc(positions_count * sizeof(int*));
    if (!positions) return 0;
    
    for (int i = 0; i < positions_count; i++) {
        positions[i] = (int*)malloc(2 * sizeof(int));
        if (!positions[i]) {
            for (int j = 0; j < i; j++) {
                free(positions[j]);
            }
            free(positions);
            return 0;
        }
    }
    
    // 填充数据
    for (int i = 0; i < positions_count && (3 + i * 2 + 1) < size; i++) {
        positions[i][0] = data[3 + i * 2] % 50;
        positions[i][1] = data[4 + i * 2] % 50;
    }
    
    if (!arePositionsUnique(positions, positions_count) ||
        !isKnightPositionValid(kx, ky, positions, positions_count)) {
        for (int i = 0; i < positions_count; i++) {
            free(positions[i]);
        }
        free(positions);
        return 0;
    }


    // TODO: Execute the test function
    int result = maxMoves(kx, ky, positions, positions_count);

    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_414_p4/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "kx = " << kx << ", ky = " << ky << ", positions = [";
    for (int i = 0; i < positions_count; i++) {
        outFile << "[" << positions[i][0] << ", " << positions[i][1] << "]";
        if (i < positions_count - 1) {
            outFile << ", ";
        }
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();

    for (int i = 0; i < positions_count; i++) {
        free(positions[i]);
    }
    free(positions);
    
    return 0;
}
