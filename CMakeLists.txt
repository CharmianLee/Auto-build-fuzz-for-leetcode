cmake_minimum_required(VERSION 3.10)
project(LeetcodeFuzzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Fuzzing flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=fuzzer,address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer,address")

# Problem: Weekly Contest 413 Problem 1
# C version
add_executable(fuzzer_c_wc413_p1
    C_CPP/C/src/weekly_contest_413_p1.c
    C_CPP/C/constraints/weekly_contest_413_p1_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc413_p1
    C_CPP/CPP/src/weekly_contest_413_p1.cpp
    C_CPP/CPP/constraints/weekly_contest_413_p1_constraint.cpp
)

# Problem: Weekly Contest 413 Problem 2
# C version
add_executable(fuzzer_c_wc413_p2
    C_CPP/C/src/weekly_contest_413_p2.c
    C_CPP/C/constraints/weekly_contest_413_p2_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc413_p2
    C_CPP/CPP/src/weekly_contest_413_p2.cpp
    C_CPP/CPP/constraints/weekly_contest_413_p2_constraint.cpp
)

# Problem: Weekly Contest 413 Problem 3
# C version
add_executable(fuzzer_c_wc413_p3
    C_CPP/C/src/weekly_contest_413_p3.c
    C_CPP/C/constraints/weekly_contest_413_p3_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc413_p3
    C_CPP/CPP/src/weekly_contest_413_p3.cpp
    C_CPP/CPP/constraints/weekly_contest_413_p3_constraint.cpp
)

# Problem: Weekly Contest 413 Problem 4
# C version
add_executable(fuzzer_c_wc413_p4
    C_CPP/C/src/weekly_contest_413_p4.c
    C_CPP/C/constraints/weekly_contest_413_p4_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc413_p4
    C_CPP/CPP/src/weekly_contest_413_p4.cpp
    C_CPP/CPP/constraints/weekly_contest_413_p4_constraint.cpp
)

# Problem: Weekly Contest 414 Problem 1
# C version
add_executable(fuzzer_c_wc414_p1
    C_CPP/C/src/weekly_contest_414_p1.c
    C_CPP/C/constraints/weekly_contest_414_p1_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc414_p1
    C_CPP/CPP/src/weekly_contest_414_p1.cpp
    C_CPP/CPP/constraints/weekly_contest_414_p1_constraint.cpp
)

# Problem: Weekly Contest 414 Problem 2
# C version
add_executable(fuzzer_c_wc414_p2
    C_CPP/C/src/weekly_contest_414_p2.c
    C_CPP/C/constraints/weekly_contest_414_p2_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc414_p2
    C_CPP/CPP/src/weekly_contest_414_p2.cpp
    C_CPP/CPP/constraints/weekly_contest_414_p2_constraint.cpp
)

# Problem: Weekly Contest 414 Problem 3
# C version
add_executable(fuzzer_c_wc414_p3
    C_CPP/C/src/weekly_contest_414_p3.c
    C_CPP/C/constraints/weekly_contest_414_p3_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc414_p3
    C_CPP/CPP/src/weekly_contest_414_p3.cpp
    C_CPP/CPP/constraints/weekly_contest_414_p3_constraint.cpp
)

# Problem: Weekly Contest 414 Problem 4
# C version
add_executable(fuzzer_c_wc414_p4
    C_CPP/C/src/weekly_contest_414_p4.c
    C_CPP/C/constraints/weekly_contest_414_p4_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc414_p4
    C_CPP/CPP/src/weekly_contest_414_p4.cpp
    C_CPP/CPP/constraints/weekly_contest_414_p4_constraint.cpp
)

# Problem: Weekly Contest 415 Problem 1
# C version
add_executable(fuzzer_c_wc415_p1
    C_CPP/C/src/weekly_contest_415_p1.c
    C_CPP/C/constraints/weekly_contest_415_p1_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc415_p1
    C_CPP/CPP/src/weekly_contest_415_p1.cpp
    C_CPP/CPP/constraints/weekly_contest_415_p1_constraint.cpp
)

# Problem: Weekly Contest 415 Problem 2
# C version
add_executable(fuzzer_c_wc415_p2
    C_CPP/C/src/weekly_contest_415_p2.c
    C_CPP/C/constraints/weekly_contest_415_p2_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc415_p2
    C_CPP/CPP/src/weekly_contest_415_p2.cpp
    C_CPP/CPP/constraints/weekly_contest_415_p2_constraint.cpp
)

# Problem: Weekly Contest 415 Problem 3
# C version
add_executable(fuzzer_c_wc415_p3
    C_CPP/C/src/weekly_contest_415_p3.c
    C_CPP/C/constraints/weekly_contest_415_p3_constraint.cpp
)

# C++ version
add_executable(fuzzer_cpp_wc415_p3
    C_CPP/CPP/src/weekly_contest_415_p3.cpp
    C_CPP/CPP/constraints/weekly_contest_415_p3_constraint.cpp
)
