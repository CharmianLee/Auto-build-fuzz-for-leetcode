#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../src/weekly_contest_413_p2.cpp"

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

// 将模糊测试输入转换为有效的函数参数
void transformInput(const uint8_t* data, size_t size,
                   vector<vector<int>>& queries, int& k) {
    // 读取k值
    k = std::max(1, abs(*reinterpret_cast<const int32_t*>(data)) % 100001);
    data += sizeof(int32_t);
    size -= sizeof(int32_t);

    // 计算可以构建的查询数量
    size_t queryCount = size / (2 * sizeof(int32_t));
    queryCount = std::min(queryCount, static_cast<size_t>(2 * 100000));

    // 构建查询
    for (size_t i = 0; i < queryCount; i++) {
        const int32_t* queryData = reinterpret_cast<const int32_t*>(data + i * 2 * sizeof(int32_t));
        // 确保x,y在[-10^9, 10^9]范围内
        int x = std::max(-1000000000, std::min(1000000000, static_cast<int>(queryData[0])));
        int y = std::max(-1000000000, std::min(1000000000, static_cast<int>(queryData[1])));
        queries.push_back({x, y});
    }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 转换输入数据
    vector<vector<int>> queries;
    int k;
    transformInput(data, size, queries, k);

    // TODO: Execute the test function
    Solution solution;
    vector<int> result = solution.resultsArray(queries, k);

    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_413_p2/output/";
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
        for (size_t i = 0; i < queries.size(); i++) {
            outFile << "[" << queries[i][0] << "," << queries[i][1] << "]";
            if (i < queries.size() - 1) outFile << ",";
        }
        outFile << "]\n";

        // 写入输出数据
        outFile << "Output: [";
        for (int i = 0; i < queries.size(); i++) {
            outFile << result[i];
            if (i < queries.size() - 1) outFile << ",";
        }
        outFile << "]\n";
        outFile << "--------------------------\n";
        outFile.close();
    }
    
    return 0;
}
