#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

extern "C"
{
    // TODO: Add your function declaration here
    // Example: bool solutionFunction(type1 param1, type2 param2);
    int *maximumSubarrayXor(int *nums, int numsSize, int **queries, int queriesSize, int *queriesColSize, int *returnSize);
}

// Add your input validation functions here
bool isValidInput(const uint8_t *data, size_t size)
{
    // 检查基本大小要求
    if (size < sizeof(int) * 2)
        return false; // 至少需要numsSize和queriesSize

    // 获取数组大小
    int numsSize = *(int *)data;
    if (numsSize < 1 || numsSize > 2000)
        return false;

    // 计算queries数组大小
    int queriesSize = *(int *)(data + sizeof(int));
    if (queriesSize < 1 || queriesSize > 100000)
        return false;

    // 检查总大小是否足够
    size_t requiredSize = sizeof(int) * 2 +              // numsSize和queriesSize
                          sizeof(int) * numsSize +       // nums数组
                          sizeof(int) * 2 * queriesSize; // queries二维数组

    return size >= requiredSize;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (!isValidInput(data, size))
        return 0;

    // TODO: Transform fuzzer input into valid function parameters
    uint32_t numsSize = *(uint32_t *)data;
    uint32_t queriesSize = *(uint32_t *)(data + 4);

    // 初始化偏移量和剩余大小
    size_t offset = sizeof(uint32_t) * 2;
    size_t remainingSize = size - offset;

    // 计算可读取的nums元素数量，防止越界
    size_t maxNums = remainingSize / sizeof(int);
    if (numsSize > maxNums) {
        numsSize = maxNums;
    }

    // 创建nums数组
    int *nums = (int *)malloc(sizeof(int) * numsSize);
    if (!nums) {
        return 0;
    }

    // 复制nums数据，并确保元素不超过2^31 - 1
    const int *nums_data = (const int *)(data + offset);
    for (uint32_t i = 0; i < numsSize; i++) {
        nums[i] = nums_data[i] & 0x7FFFFFFF; // 确保nums[i] <= 2^31 - 1
    }

    offset += numsSize * sizeof(int);
    remainingSize = size - offset;

    // 创建queries数组
    int **queries = (int **)malloc(sizeof(int *) * queriesSize);
    int *queriesColSize = (int *)malloc(sizeof(int) * queriesSize);
    if (!queries || !queriesColSize)
    {
        free(nums);
        free(queries);
        free(queriesColSize);
        return 0;
    }

    const int *queries_data = (const int *)(data + 8 + numsSize * sizeof(int));
    for (uint32_t i = 0; i < queriesSize; i++)
    {
        queries[i] = (int *)malloc(sizeof(int) * 2);
        if (!queries[i])
        {
            // 清理内存
            for (uint32_t j = 0; j < i; j++)
            {
                free(queries[j]);
            }
            free(nums);
            free(queries);
            free(queriesColSize);
            return 0;
        }
        int l = queries_data[2 * i] % numsSize;
        int r = queries_data[2 * i + 1] % numsSize;
        if (l > r)
        {
            int temp = l;
            l = r;
            r = temp;
        }
        queries[i][0] = l;
        queries[i][1] = r;
        queriesColSize[i] = 2;
    }

    // TODO: Execute the test function
    int returnSize;
    int *result = maximumSubarrayXor(nums, numsSize, queries, queriesSize, queriesColSize, &returnSize);

    // Save test case
    std::string outputDir = "fuzz_outputs/C/weekly_contest_413_p4/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }

    outFile << "Input: nums = [";
    for (int i = 0; i < numsSize; i++)
    {
        outFile << nums[i];
        if (i < numsSize - 1)
            outFile << ", ";
    }
    outFile << "], ";

    outFile << "queries = [";
    for (int i = 0; i < queriesSize; i++)
    {
        outFile << "[" << queries[i][0] << ", " << queries[i][1] << "]";
        if (i < queriesSize - 1)
            outFile << ", ";
    }
    outFile << "]" << std::endl;

    outFile << "Output: [";
    for (int i = 0; i < returnSize; i++)
    {
        outFile << result[i];
        if (i < returnSize - 1)
            outFile << ", ";
    }
    outFile << "]" << std::endl;
    outFile << "--------------------------" << std::endl;

    // 清理内存
    free(nums);
    for (int i = 0; i < queriesSize; i++)
    {
        free(queries[i]);
    }
    free(queries);
    free(queriesColSize);
    free(result);

    return 0;
}
