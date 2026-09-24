# EECE 7205 (FCE) — Assignment 1

This repository contains the source code, results, and test suite for **Assignment 1** in **EECE 7205 (Fundamentals of Computer Engineering)**.

---

##  Repository Structure

```text
EECE 7205 (FCE)/
└── Assignment 1/
    ├── src/
    │   ├── Assignment1(FCE)_Bidnurmath.cpp   # Main assignment solutions
    │   ├── echo_main.cpp                     # Helper source file to record inputs & outputs
    │   ├── main.echo.exe                     # Compiled test executable
    │   └── main_test                         # Additional test runner/executable
    ├── results/
    │   ├── results.txt                       # Output containing full validation & invalid input tests
    │   ├── results_valid.txt                 # Output containing valid test cases and edge cases only
    │   └── test_cases_used/
    │       ├── test_cases_typed_out.txt      # Input cases testing input validation bounds
    │       └── test_cases_valid_only.txt     # Input cases with standard and edge cases only
    └── Questions/                            # Assignment prompt and questions

Compilation & Execution Instructions
Prerequisites
C++ Compiler: g++ with C++17 support standard.

Shell Environment: PowerShell or Bash.

Compiling the Source Code
To compile the main source code or the testing setup using g++:

PowerShell
g++ -std=c++17 echo_main.cpp -o main_echo.exe
🧪 Test Execution Pipeline & Output Generation
Test Execution Strategy
test_cases_typed_out.txt: Contains terminal inputs designed to stress-test input validation bounds, error handling, and invalid inputs.

test_cases_valid_only.txt: Contains standard test cases, normal operational bounds, and mathematical edge cases (e.g., empty arrays, duplicates, tie-breaker scenarios) without input validation triggers.

Automated Testing via PowerShell
To record inputs and verify exact program behaviors against terminal input streams, execution logs were piped using PowerShell:

PowerShell
Get-Content test_cases_valid_only.txt | .\main_echo.exe > results_valid.txt
Result Files Overview
results.txt: Output results including all input validation bound checking and error handling outputs.

results_valid.txt: Output results for standard operation cases, core algorithmic verification, and numerical edge cases.