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
    char* convertDateToBinary(char* date);
}

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {
    // TODO: Implement input validation
    // 仅当输入长度为8时，才认为是有效输入
    if (size != 8) return false;
    return true;
}

char* buildInput(const uint8_t* data, size_t size) {
    if (size < 8) {
        return NULL; // 确保数据长度足够
    }

    int year = 1900 + data[0] % 201; // 年份范围 1900-2100
    int month = 1 + data[1] % 12;    // 月份范围 1-12
    int day = 1 + data[2] % 31;      // 日期范围 1-31

    char* inputDate = (char*)calloc(11, sizeof(char));
    if (inputDate == NULL) {
        return NULL; // 确保内存分配成功
    }

    snprintf(inputDate, 11, "%04d-%02d-%02d", year, month, day);

    return inputDate;
}

bool isValidDate(const char* date) {
    // 日期格式为"yyyy-mm-dd"
    // 输入保证 date 代表一个有效的公历日期，日期范围从 1900 年 1 月 1 日到 2100 年 12 月 31 日（包括这两天）。
    if (date[4] != '-' || date[7] != '-') return false;
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);
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
    // 构建符合"yyyy-mm-dd"格式的日期字符串
    char* inputDate = buildInput(data, size);
    if (inputDate == NULL) {
        return 0;
    }

    if (!isValidDate(inputDate))
    {
        free(inputDate);
        return 0;
    }

    // TODO: Execute the test function
    // 调用 convertDateToBinary 方法
    char* result = convertDateToBinary(inputDate);
    
    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_414_p1/output/";
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

    free(inputDate);
    free(result);
    
    return 0;
}
