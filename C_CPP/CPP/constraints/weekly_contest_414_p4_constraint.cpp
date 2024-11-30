#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_414_p4.cpp" 

// Add your input validation functions here
bool isValidPosition(int x, int y) {
    return x >= 0 && x <= 49 && y >= 0 && y <= 49;
}

bool isValidPositionsSize(size_t size) {
    return size >= 1 && size <= 15;
}

bool arePositionsUnique(const vector<vector<int>>& positions) {
    for (size_t i = 0; i < positions.size(); i++) {
        for (size_t j = i + 1; j < positions.size(); j++) {
            if (positions[i][0] == positions[j][0] && positions[i][1] == positions[j][1]) {
                return false;
            }
        }
    }
    return true;
}

bool isKnightPositionValid(int kx, int ky, const vector<vector<int>>& positions) {
    for (const auto& pos : positions) {
        if (pos[0] == kx && pos[1] == ky) {
            return false;
        }
    }
    return true;
}

bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // Minimum required size: kx(1) + ky(1) + positions_count(1) + at least one position(2) = 5 bytes
    if (size < 5) return false;
    
    int kx = data[0];
    int ky = data[1];
    size_t positions_count = data[2];
    
    // Check if we have enough bytes for all positions
    if (size < 3 + positions_count * 2) return false;
    
    // Validate knight position
    if (!isValidPosition(kx, ky)) return false;
    
    // Validate positions count
    if (!isValidPositionsSize(positions_count)) return false;
    
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // Transform fuzzer input into valid parameters
    int kx = data[0] % 50;  // Ensure 0-49 range
    int ky = data[1] % 50;
    size_t positions_count = data[2] % 15 + 1;  // Ensure 1-15 range
    
    // Create positions vector
    vector<vector<int>> positions;
    for (size_t i = 0; i < positions_count && (3 + i * 2 + 1) < size; i++) {
        int x = data[3 + i * 2] % 50;
        int y = data[4 + i * 2] % 50;
        positions.push_back({x, y});
    }
    
    // Additional validation
    if (!arePositionsUnique(positions)) return 0;
    if (!isKnightPositionValid(kx, ky, positions)) return 0;

    // TODO: Execute the test function
    Solution solution;
    int result = solution.maxMoves(kx, ky, positions);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_414_p4/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "kx = " << kx << ", ky = " << ky << ", positions = [";
    for (size_t i = 0; i < positions.size(); i++) {
        outFile << "[" << positions[i][0] << ", " << positions[i][1] << "]";
        if (i < positions.size() - 1) {
            outFile << ", ";
        }
    }
    outFile << "]" << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
