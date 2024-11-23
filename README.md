# LeetCode Contest Fuzzing Project

这是一个针对LeetCode竞赛题目的自动化Fuzzing测试项目。
该项目旨在通过模糊测试(Fuzzing)技术，为LeetCode竞赛题目生成大量有效的测试用例。
后续可添加：通过随机数变异寻找边界。

## 项目结构

```
fuzz_test_project/
├── C_CPP/
│   ├── C/                     # C语言实现
│   │   ├── src/              # C源文件
│   │   └── constraints/      # C语言约束文件
│   └── CPP/                  # C++实现
│       ├── src/              # C++源文件
│       └── constraints/      # C++约束文件
├── fuzz_outputs/             # Fuzzing输出结果
│   ├── C/                    # C语言测试结果
│   └── CPP/                  # C++测试结果
├── scripts/                  # 自动化脚本
│   ├── template_generator.py # 模板生成器
│   └── batch_runner.py      # 批量测试运行器
├── CMakeLists.txt           # CMake构建配置
└── README.md                # 项目文档
```

## 环境要求

- Python 3.7+
- CMake 3.10+
- Clang/LLVM (支持LibFuzzer)
- Unix-like环境 (Linux/macOS)

### 安装依赖

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y cmake clang llvm python3 python3-pip

# macOS
brew install cmake llvm python3
```

## 快速开始

### 1. 克隆项目

```bash
git clone <repository_url>
cd fuzz_test_project
```

### 2. 生成题目模板

使用template_generator.py为特定竞赛题目生成测试模板：

```bash
# 为第413场周赛第1题生成模板
python scripts/template_generator.py 413 1
```

这将创建：
- C/C++源文件模板
- Fuzzing约束文件模板
- 配置文件
- 更新CMakeLists.txt

### 3. 完善模板

生成模板后，需要手动根据题解完成以下工作：

1. 在源文件中实现题目的解决方案：
   - `C_CPP/C/src/weekly_contest_413_p1.c`
   - `C_CPP/CPP/src/weekly_contest_413_p1.cpp`

2. 在约束文件中实现输入生成逻辑与数据收集逻辑：
   - `C_CPP/C/constraints/weekly_contest_413_p1_constraint.cpp`
   - `C_CPP/CPP/constraints/weekly_contest_413_p1_constraint.cpp`

3. 在JSON配置文件中设置合适的参数：
   - `C_CPP/C/constraints/weekly_contest_413_p1.json`
   - `C_CPP/CPP/constraints/weekly_contest_413_p1.json`

### 4. 运行测试

#### 单个题目测试

```bash
# 运行特定题目的测试（例如：413场第1题的C++实现）
python scripts/batch_runner.py --contest 413 --problem 1 --language CPP

# 运行特定题目的所有语言实现
python scripts/batch_runner.py --contest 413 --problem 1
```

#### 批量测试

```bash
# 运行所有已实现题目的测试
python scripts/batch_runner.py --batch or --all or no args

# 使用特定数量的并行进程运行批量测试
python scripts/batch_runner.py --batch --max-workers 8
```

### 5. 查看结果

测试结果将保存在`fuzz_outputs`目录下：

```bash
# 查看C版本的测试结果
cat fuzz_outputs/C/weekly_contest_413_p1/output/test_cases.txt

# 查看C++版本的测试结果
cat fuzz_outputs/CPP/weekly_contest_413_p1/output/test_cases.txt
```

测试语料将保存在`corpus`目录下。

## 添加新的题目

1. 使用template_generator.py生成模板：
```bash
python scripts/template_generator.py <contest_number> <problem_number>
```

2. 实现必要的文件：
   - 在`src`目录下实现题目解决方案
   - 在`constraints`目录下实现Fuzzing约束
   - 配置JSON文件中的参数

3. 运行测试：
```bash
python scripts/batch_runner.py --contest <contest_number> --problem <problem_number>
```

## 配置文件说明

每个题目的JSON配置文件包含以下主要字段：

```json
{
    "fuzzing_params": {
        "max_len": 100,     // 最大输入长度
        "max_time": 30,     // 最大运行时间(秒)
        "runs": 100000      // 测试运行次数
    },
    "problem_info": {
        "contest": "Weekly Contest XXX",
        "problem_number": N,
        "title": "问题标题",
        "difficulty": "难度",
        "source_url": "题目链接",
        "tags": ["标签1", "标签2"]
    }
}
```

## 建议的工作流程

1. 使用template_generator.py生成新题目的模板
2. 实现题目的解决方案
3. 根据题目要求修改约束文件
4. 调整配置文件中的参数
5. 运行测试并分析结果
6. 根据测试结果优化实现和约束

## 注意事项

1. 确保环境中已正确安装所有依赖
2. 运行Fuzzing测试前先检查配置文件参数
3. 对于大型批量测试，建议适当调整并行进程数
4. 定期检查和清理fuzz_outputs目录以节省磁盘空间
5. 在提交代码前进行完整的测试运行

## 故障排除

### 常见问题

1. 编译错误
   - 检查CMake和编译器版本
   - 确保所有必要的头文件都已包含
   - 验证源文件的语法正确性

2. Fuzzing运行时错误
   - 检查约束文件中的输入验证逻辑
   - 确保内存操作安全
   - 验证配置文件参数的合理性

3. 输出文件为空
   - 检查输出文件路径权限
   - 确认约束文件中的文件操作正确
   - 验证测试函数是否正确执行