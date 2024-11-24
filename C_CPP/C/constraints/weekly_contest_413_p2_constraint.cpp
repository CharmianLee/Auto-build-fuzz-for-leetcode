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
    int* resultsArray(int** queries, int queriesSize, int* queriesColSize, int k, int* returnSize);
}

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // 检查基本大小要求
    if (size < sizeof(int32_t) * 3) { // 至少需要k值和一个查询点(x,y)
        return false;
    }

    // 获取查询数量
    const size_t minQuerySize = sizeof(int32_t) * 2; // 每个查询需要两个int32_t (x,y)
    size_t maxQueries = (size - sizeof(int32_t)) / minQuerySize; // 减去k值的空间

    // 检查查询数量是否在合理范围内 (1 <= queries.length <= 2 * 10^5)
    if (maxQueries < 1 || maxQueries > 2 * 100000) {
        return false;
    }

    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 从输入数据中提取k值
    int k = std::max(1, abs(*reinterpret_cast<const int32_t*>(data)) % 100001);
    data += sizeof(int32_t);
    size -= sizeof(int32_t);
    
    // 计算查询数量并分配内存
    size_t queryCount = std::min(size / (2 * sizeof(int32_t)), 
                                static_cast<size_t>(2 * 100000));
    
    // 分配内存
    int** queries = (int**)malloc(queryCount * sizeof(int*));
    int* queriesColSize = (int*)malloc(queryCount * sizeof(int));
    for (size_t i = 0; i < queryCount; i++) {
        queries[i] = (int*)malloc(2 * sizeof(int));
        queriesColSize[i] = 2;
    }
    
    // 填充查询数据
    for (size_t i = 0; i < queryCount; i++) {
        const int32_t* queryData = reinterpret_cast<const int32_t*>(data + i * 2 * sizeof(int32_t));
        queries[i][0] = std::max(-1000000000, 
                                std::min(1000000000, static_cast<int>(queryData[0])));
        queries[i][1] = std::max(-1000000000, 
                                std::min(1000000000, static_cast<int>(queryData[1])));
    }

    // TODO: Execute the test function
    int returnSize;
    int* result = resultsArray(queries, queryCount, queriesColSize, k, &returnSize);

    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_413_p2/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    
    if (outFile.is_open()) {
        // 写入输入数据
        outFile << "Input: k = " << k << ", queries = [";
        for (size_t i = 0; i < returnSize; i++) {
            outFile << "[" << queries[i][0] << "," << queries[i][1] << "]";
            if (i < returnSize - 1) outFile << ",";
        }
        outFile << "]\n";

        // 写入输出数据
        outFile << "Output: [";
        for (int i = 0; i < returnSize; i++) {
            outFile << result[i];
            if (i < returnSize - 1) outFile << ",";
        }
        outFile << "]\n";
        outFile << "--------------------------\n";
        outFile.close();
    }
    
    // 释放内存
    for (size_t i = 0; i < queryCount; i++) {
        free(queries[i]);
    }
    free(queries);
    free(queriesColSize);
    free(result);
    
    return 0;
}
