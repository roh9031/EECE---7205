# EECE 7205 (FCE) — Assignments 

This repository contains the source code, results, and test suite for **Assignment 1** and **Assignemnt 2** in **EECE 7205 (Fundamentals of Computer Engineering)**.

---


## Repository Structure

```text
EECE 7205 (FCE)/
├── Assignment 1/
│   ├── src/
│   │   ├── Assignment1(FCE)_Bidnurmath.cpp    # Main assignment solutions
│   │   ├── echo_main.cpp                      # Helper source file to record inputs & outputs
│   │   ├── main.echo.exe                      # Compiled test executable
│   │   └── main_test                          # Additional test runner/executable
│   ├── results/
│   │   |__ Assignment1(FCE)_Bidnurmath.pdf    # PDF file report containing explanations and pseudocode
│   │   ├── results.txt                        # Output containing full validation & invalid input tests
│   │   ├── results_valid.txt                  # Output containing valid test cases and edge cases only
│   │   ├── test_cases_typed_out.txt           # Input cases testing input validation bounds
│   │   └── test_cases_valid_only.txt          # Input cases with standard and edge cases only
│   └── questions/
│       |__ Problems_Assignment_1.pdf          # Assignment questions
│
└── Assignment 2/
    ├── src/
    │   ├── Assignment_2_FCE_Bidnurmath.cpp    # Main OOP binary tree solutions (Questions 1–15)
    │   ├── runner.cpp                         # Helper source file to record inputs & outputs via EchoBuf
    │   └── assignment2_run.exe                # Compiled test executable
    ├── results/
    │   ├── Assignment_2_FCE_Bidnurmath.pdf    # PDF file report containing explanations and pseudocode
    │   ├── output.txt                        # Output containing results
    │   
    └── questions/
        └── Problems_Assignment_2.pdf          # Assignment questions


Compilation & Execution Instructions (Assignment 2)
1. Prerequisites
C++ Compiler: g++ with C++17 support standard.

Shell Environment: PowerShell (Windows) or Bash.

2. Compiling the Source Code
Navigate to your Assignment 2 src directory and compile runner.cpp (which automatically hooks into and runs Assignment_2_FCE_Bidnurmath.cpp):

PowerShell
cd "EECE 7205(FCE)\Assignment 2\src"
g++ runner.cpp -o assignment2_run.exe
3. Execution & Output Generation
To run the compiled test executable and generate/capture your outputs into a text file, use PowerShell redirection:

PowerShell
.\assignment2_run.exe > output.txt





Compilation & Execution Instructions (Assignment 1)
Prerequisites
C++ Compiler: g++ with C++17 support standard.

Shell Environment: PowerShell or Bash.

Compiling the Source Code
To compile the main source code or the testing setup using g++:

PowerShell
g++ -std=c++17 echo_main.cpp -o main_echo.exe

Test Execution Pipeline & Output Generation
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