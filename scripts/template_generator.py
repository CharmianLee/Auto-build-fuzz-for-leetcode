import os
import argparse
import json
from typing import Dict, Any, List, Optional
import sys

class TemplateGenerator:
    def __init__(self, contest_num: int, problem_num: int):
        self.contest_num = contest_num
        self.problem_num = problem_num
        self.base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        self.problem_id = f"weekly_contest_{contest_num}_p{problem_num}"

    def create_directory_structure(self):
        """创建项目目录结构"""
        dirs = [
            f"C_CPP/C/src",
            f"C_CPP/C/constraints",
            f"C_CPP/CPP/src",
            f"C_CPP/CPP/constraints",
            f"fuzz_outputs/C/{self.problem_id}/corpus",
            f"fuzz_outputs/C/{self.problem_id}/output",
            f"fuzz_outputs/CPP/{self.problem_id}/corpus",
            f"fuzz_outputs/CPP/{self.problem_id}/output"
        ]
        for dir_path in dirs:
            os.makedirs(os.path.join(self.base_dir, dir_path), exist_ok=True)

    def generate_c_source(self) -> str:
        """生成C源文件模板"""
        return f"""// Problem: Weekly Contest {self.contest_num} Problem {self.problem_num}
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// TODO: Add your function declaration here
// Example:
// bool solutionFunction(type1 param1, type2 param2) {{
//     // Implementation
// }}
"""

    def generate_cpp_source(self) -> str:
        """生成C++源文件模板"""
        return f"""// Problem: Weekly Contest {self.contest_num} Problem {self.problem_num}
#include <string>
#include <vector>
using namespace std;

class Solution {{
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {{
    //     // Implementation
    // }}
}};
"""

    def generate_constraint_template(self, language: str) -> str:
        """生成约束文件模板"""
        if language == "C":
            extern_c = """extern "C" {
    // TODO: Add your function declaration here
    // Example: bool solutionFunction(type1 param1, type2 param2);
}"""
        else:
            extern_c = f"""#include "../src/{self.problem_id}.cpp" """

        return f"""#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <filesystem>

{extern_c}

// Add your input validation functions here
bool isValidInput(const uint8_t* data, size_t size) {{
    // TODO: Implement input validation
    return true;
}}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {{
    if (!isValidInput(data, size)) return 0;
    
    // TODO: Transform fuzzer input into valid function parameters
    
    // TODO: Execute the test function
    
    // Save test case
    std::string outputDir = "fuzz_outputs/{language}/{self.problem_id}/output/";
    // 创建输出目录（如果不存在）
    std::filesystem::create_directories(outputDir);
    std::ofstream outFile;
    outFile.open(outputDir + "test_cases.txt", std::ios::app);
    if (!outFile.is_open()) {{
        std::cerr << "无法打开输出文件！" << std::endl;
        return 0;
    }}
    outFile << "Input: " << "TODO: Format input" << std::endl;
    outFile << "Output: " << "TODO: Format output" << std::endl;
    outFile << "--------------------------" << std::endl;
    outFile.close();
    
    return 0;
}}
"""

    def generate_json_config(self) -> Dict[str, Any]:
        """生成JSON配置文件模板"""
        return {
            "fuzzing_params": {
                "max_len": 100,  # TODO: Adjust based on problem
                "max_time": 30,
                "runs": 100000
            },
            "problem_info": {
                "contest": f"Weekly Contest {self.contest_num}",
                "problem_number": self.problem_num,
                "title": "TODO: Add problem title",
                "difficulty": "TODO: Add difficulty",
                "source_url": f"https://leetcode.con/problems/...",
                "tags": ["TODO", "Add", "Tags"]
            }
        }

    def generate_cmakelists(self) -> str:
        """生成CMakeLists.txt模板"""
        cmakelists_path = os.path.join(self.base_dir, "CMakeLists.txt")
        cmakelists_header = """cmake_minimum_required(VERSION 3.10)
project(LeetcodeFuzzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Fuzzing flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=fuzzer,address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer,address")
"""

        cmakelists_body = f"""
# Problem: Weekly Contest {self.contest_num} Problem {self.problem_num}
# C version
add_executable(fuzzer_c_wc{self.contest_num}_p{self.problem_num}
    C_CPP/C/src/{self.problem_id}.c
    C_CPP/C/constraints/{self.problem_id}_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc{self.contest_num}_p{self.problem_num}
    C_CPP/CPP/src/{self.problem_id}.cpp
    C_CPP/CPP/constraints/{self.problem_id}_constraint.cpp
)
"""
        
        # 读取CMakeLists.txt文件，如果已包含header配置则只追加body
        if os.path.exists(cmakelists_path):
            with open(cmakelists_path, 'r') as f:
                content = f.read()
            if cmakelists_header not in content:
                with open(cmakelists_path, 'a') as f:
                    f.write(cmakelists_header)
        else:
            with open(cmakelists_path, 'w') as f:
                f.write(cmakelists_header)

        with open(cmakelists_path, 'a') as f:
            f.write(cmakelists_body)
                


    def generate_template(self):
        """生成所有模板文件"""
        # 创建目录结构
        self.create_directory_structure()
        
        # 生成源文件
        with open(os.path.join(self.base_dir, f"C_CPP/C/src/{self.problem_id}.c"), 'w') as f:
            f.write(self.generate_c_source())
        
        with open(os.path.join(self.base_dir, f"C_CPP/CPP/src/{self.problem_id}.cpp"), 'w') as f:
            f.write(self.generate_cpp_source())
        
        # 生成约束文件
        for lang in ["C", "CPP"]:
            with open(os.path.join(self.base_dir, f"C_CPP/{lang}/constraints/{self.problem_id}_constraint.cpp"), 'w') as f:
                f.write(self.generate_constraint_template(lang))
            
            with open(os.path.join(self.base_dir, f"C_CPP/{lang}/constraints/{self.problem_id}.json"), 'w') as f:
                json.dump(self.generate_json_config(), f, indent=4)
        
        # 生成CMakeLists.txt
        self.generate_cmakelists()
        
        # 生成输出文件
        with open(os.path.join(self.base_dir, f"fuzz_outputs/C/{self.problem_id}/output/test_cases.txt"), 'w') as f:
            f.write("Correct test cases:\n")
        with open(os.path.join(self.base_dir, f"fuzz_outputs/CPP/{self.problem_id}/output/test_cases.txt"), 'w') as f:
            f.write("Correct test cases:\n")

def main():
    parser = argparse.ArgumentParser(description='Generate fuzzing test templates for LeetCode problems')
    parser.add_argument('contest_num', type=int, help='LeetCode contest number')
    parser.add_argument('problem_num', type=int, help='Problem number within the contest (1-4)')
    
    args = parser.parse_args()
    
    if not (1 <= args.problem_num <= 4):
        print("Error: Problem number must be between 1 and 4")
        sys.exit(1)
    
    generator = TemplateGenerator(args.contest_num, args.problem_num)
    generator.generate_template()
    print(f"Successfully generated templates for Weekly Contest {args.contest_num} Problem {args.problem_num}")

if __name__ == "__main__":
    main()