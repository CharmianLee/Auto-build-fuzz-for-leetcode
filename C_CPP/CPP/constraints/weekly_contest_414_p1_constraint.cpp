#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../src/weekly_contest_414_p1.cpp" 

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // 仅当输入长度为8时，才认为是有效输入（8个数字）
    if (size != 8) return false;
    return true;
}

string buildInput(const uint8_t* data, size_t size) {
    // 将Fuzzer输入（字节数组）转化为字符串（日期格式）
    string inputDate;
    string year = to_string(data[0] * 1000 + data[1] * 100 + data[2] * 10 + data[3]);
    string month = to_string(data[4] * 10 + data[5]);
    string day = to_string(data[6] * 10 + data[7]);
    inputDate = year + "-" + month + "-" + day;
    return inputDate;
}

bool isValidDate(const std::string& date) {
    // 日期格式为"yyyy-mm-dd"
    // 输入保证 date 代表一个有效的公历日期，日期范围从 1900 年 1 月 1 日到 2100 年 12 月 31 日（包括这两天）。
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2) {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    // 将Fuzzer输入（字节数组）转化为字符串（日期格式）
    std::string inputDate = buildInput(data, size);
    if (!isValidDate(inputDate)) return 0;
    
    // TODO: Execute the test function
    // 创建 Solution 类的对象，并调用 convertDateToBinary 方法
    Solution solution;
    std::string result = solution.convertDateToBinary(inputDate);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/CPP/weekly_contest_414_p1/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }
    outFile << "Input: " << "date = " << inputDate << std::endl;
    outFile << "Output: " << result << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}
