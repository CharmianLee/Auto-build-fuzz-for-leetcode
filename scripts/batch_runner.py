import os
import argparse
import json
import subprocess
import concurrent.futures
import sys
from typing import List, Optional, Tuple
import glob

class FuzzingRunner:
    def __init__(self, base_dir: str):
        self.base_dir = base_dir
        self.build_dir = os.path.join(base_dir, "build")

    def find_all_problems(self) -> List[Tuple[int, int]]:
        """查找所有已生成的问题模板"""
        problems = []
        pattern = os.path.join(self.base_dir, "C_CPP/C/src/weekly_contest_*_p*.c")
        for path in glob.glob(pattern):
            filename = os.path.basename(path)
            if filename.startswith("weekly_contest_") and filename.endswith(".c"):
                parts = filename[:-2].split("_")  # Remove .c
                if len(parts) >= 4:
                    contest_num = int(parts[2])
                    problem_num = int(parts[3][1:])
                    problems.append((contest_num, problem_num))
        return sorted(problems)

    def build_project(self) -> bool:
        """构建项目"""
        try:
            os.makedirs(self.build_dir, exist_ok=True)
            subprocess.run(["cmake", "..", "-DCMAKE_BUILD_TYPE=Release"], 
                         cwd=self.build_dir, check=True)
            subprocess.run(["cmake", "--build", "."], 
                         cwd=self.build_dir, check=True)
            return True
        except subprocess.CalledProcessError:
            print("Error: Build failed")
            return False

    def run_single_fuzzer(self, contest_num: int, problem_num: int, 
                         language: Optional[str] = None) -> bool:
        """运行单个问题的fuzzer"""
        if not self.build_project():
            return False

        problem_id = f"weekly_contest_{contest_num}_p{problem_num}"
        
        languages = ["C", "CPP"] if language is None else [language]
        success = True
        
        for lang in languages:
            try:
                # 读取配置
                config_path = os.path.join(self.base_dir, 
                    f"C_CPP/{lang}/constraints/{problem_id}.json")
                with open(config_path, 'r') as f:
                    config = json.load(f)
                
                # 准备输出目录
                output_dir = os.path.join(self.base_dir, 
                    f"fuzz_outputs/{lang}/{problem_id}")
                os.makedirs(os.path.join(output_dir, "corpus"), exist_ok=True)
                os.makedirs(os.path.join(output_dir, "output"), exist_ok=True)
                
                # 运行fuzzer
                fuzzer_path = os.path.join(self.build_dir, 
                    f"fuzzer_{lang.lower()}_wc{contest_num}_p{problem_num}")
                
                cmd = [
                    fuzzer_path,
                    f"-max_len={config['fuzzing_params']['max_len']}",
                    f"-max_total_time={config['fuzzing_params']['max_time']}",
                    f"-runs={config['fuzzing_params']['runs']}",
                    f"-artifact_prefix={os.path.join(output_dir, 'output')}/",
                    os.path.join(output_dir, "corpus")
                ]
                
                print(f"Running {lang} fuzzer for Contest {contest_num} Problem {problem_num}")
                subprocess.run(cmd, check=True)
                
            except Exception as e:
                print(f"Error running {lang} fuzzer for Contest {contest_num} "
                      f"Problem {problem_num}: {str(e)}")
                success = False
        
        return success

    def run_batch(self, problems: Optional[List[Tuple[int, int]]] = None, 
                 max_workers: int = 1) -> bool:
        """批量运行fuzzing测试"""
        if not self.build_project():
            return False
        
        if problems is None:
            problems = self.find_all_problems()
        
        if not problems:
            print("No problems found to test")
            return False
        
        success = True
        with concurrent.futures.ThreadPoolExecutor(max_workers=max_workers) as executor:
            futures = [
                executor.submit(self.run_single_fuzzer, contest_num, problem_num)
                for contest_num, problem_num in problems
            ]
            
            for future in concurrent.futures.as_completed(futures):
                try:
                    if not future.result():
                        success = False
                except Exception as e:
                    print(f"Error in fuzzer execution: {str(e)}")
                    success = False
        
        return success

def main():
    parser = argparse.ArgumentParser(description='Run fuzzing tests for LeetCode problems')
    parser.add_argument('--contest', type=int, help='Contest number')
    parser.add_argument('--problem', type=int, help='Problem number (1-4)')
    parser.add_argument('--language', choices=['C', 'CPP'], help='Language to run')
    parser.add_argument('--all', action='store_true', help='Run all problems')
    parser.add_argument('--batch', action='store_true', help='Run all problems')
    parser.add_argument('--max_workers', type=int, default=4, help='Maximum number of workers')
    
    args = parser.parse_args()
    
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    runner = FuzzingRunner(base_dir)
    
    if args.contest is not None and args.problem is not None:
        if not (1 <= args.problem <= 4):
            print("Error: Problem number must be between 1 and 4")
            return False
        if args.language is not None:
            success = runner.run_single_fuzzer(args.contest, args.problem, args.language)
        else:
            success = runner.run_single_fuzzer(args.contest, args.problem)
    elif args.all:
        success = runner.run_batch()
    elif args.batch:
        if args.max_workers is not None:
            success = runner.run_batch(max_workers=args.max_workers)
        else:
            success = runner.run_batch()
    else:
        success = runner.run_batch()
    
    return success

if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)