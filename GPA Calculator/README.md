# GPA Calculator

## Overview
This is a simple console-based C++ application designed to calculate a student's Grade Point Average (GPA). The program prompts the user for the number of courses, takes individual letter grades and credit hours for each, validates the entries, and computes a weighted final GPA.

## Features
* **Standard 4.0 Scale:** Supports grades from A+ down to F.
* **Input Validation:** Catches invalid inputs for course counts, ignores unrecognized letter grades until a correct one is provided, and ensures credit hours are positive numbers.
* **Buffer Safety:** Clears input streams to prevent infinite loop errors.

## Grade Scale Reference
The program maps letter grades to the following numeric quality points:

| Grade | Points | | Grade | Points | | Grade | Points |
| :---: | :----: | | :---: | :----: | | :---: | :----: |
| **A+** | 4.0   | | **B-** | 2.7   | | **D+** | 1.3   |
| **A**  | 4.0   | | **C+** | 2.3   | | **D**  | 1.0   |
| **A-** | 3.7   | | **C**  | 2.0   | | **F**  | 0.0   |
| **B+** | 3.3   | | **C-** | 1.7   | |        |       |
| **B**  | 3.0   | |        |       | |        |       |

## How to Compile and Run

### Prerequisites
You need a C++ compiler installed (such as `g++` or `clang`) that supports the C++11 standard or higher (required for `std::unordered_map`).

### Compilation
Open your terminal or command prompt inside this folder and run the following command:

```bash
g++ -std=c++11 "GPA CALULATOR.cpp" -o gpa_calculator
```

### Execution
Run the compiled executable from your terminal:

* **Windows:**
  ```cmd
  gpa_calculator.exe
  ```
* **Mac / Linux:**
  ```bash
  ./gpa_calculator
  ```
