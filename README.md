# APC — Arbitrary Precision Calculator (C Project)

## 📌 Overview
The **APC (Arbitrary Precision Calculator)** is a C program that performs **addition**, **subtraction**, **multiplication**, and **division** on **very large integers** that cannot be stored in standard C data types like `int` or `long long`.

It represents each number as a **doubly linked list of digits**, which lets the program work with numbers that have hundreds or even thousands of digits without overflow.

Language composition: C (100%)

---

## 🚀 Features
- ✅ Handles **arbitrarily large integers** (limited only by available memory)  
- ✅ Supports **positive & negative integers**  
- ✅ Four operations:  
  - **Addition** (`+`)  
  - **Subtraction** (`-`)  
  - **Multiplication** (`x` instead of `*`)  
  - **Division** (`/`)  
- ✅ Removes **leading zeros** in results  
- ✅ Input validation for invalid operators and non-digit operands  
- ✅ Graceful handling of edge cases, for example:  
  - Adding/Subtracting zero  
  - Multiplication by zero  
  - Division by zero

---

## 🛠 Data Structures Used
- **`Dlist` (Doubly Linked List)**  
  Each digit is stored in a separate node, allowing easy traversal in both forward and backward directions.
- **`Data` struct**  
  Stores sizes, sign flags, and a swap flag for operands.

---

## 📂 Project Structure
- `apc.h`                → Main macro definitions, data structures, function prototypes  
- `common.h`             → Prototypes for helper/common functions  
- `main.c`               → Program entry point and command handling  
- `validate_args(...)`   → Validates user input arguments  
- `operand_node(...)`    → Creates linked list representation of operands  
- `addition.c`           → Addition logic for large numbers  
- `subtraction.c`        → Subtraction logic for large numbers  
- `multiplication.c`     → Multiplication logic for large numbers  
- `division.c`           → Division logic for large numbers  
- helper functions:  
  - `print_list(...)`  
  - `insert_first(...)`  
  - `remove_zeros(...)`  
  - `delete_list(...)`  
  - `Swap(...)`

---

## 🔨 Compilation
Compile all `.c` source files together. For example:

```bash
gcc main.c addition.c subtraction.c multiplication.c division.c common.c -o apc
```

> Replace `common.c` with the actual filename that holds the helper functions if it is named differently.

---

## ▶️ Usage
Run the compiled program from the command line:

```bash
./apc
```

Operators:
- `+` → Addition
- `-` → Subtraction
- `x` → Multiplication (use lowercase `x` instead of `*`)
- `/` → Division

---

### Examples:
```bash
./apc 123456789123456789 + 987654321987654321
# Output: 1111111111111111110

./apc 999999999999999999 x 999999999999999999
# Output: 999999999999999998000000000000000001

./apc -5000 - 15000
# Output: -20000

./apc 123456789 / 0
# Output: ERROR : Division by zero
```

---

## 🔍 Edge Cases Handled
- Leading zeros in operands or results are removed.  
- Negative sign is only allowed at the **start** of an operand.  
- Different operand sizes are handled via **padding** and **swapping** as needed.  
- The program can auto-switch between addition and subtraction when operands have different signs.  
- Division by zero produces an error message.

---

## 📜 How It Works Internally
1. **Argument Validation**  
   Ensures correct number of arguments, a valid operator, and integer-only operands.  
2. **Linked List Creation**  
   Converts each operand string into a doubly linked list of digits.  
3. **Operation Execution**  
   Calls the respective function based on the operator provided.  
4. **Result Storage & Output**  
   Stores the result digit-by-digit in a separate linked list, removes any leading zeros, and prints the final number.

---

## 👨‍💻 Author
- **Name**: Anuraj R  
- **Project**: APC — Arbitrary Precision Calculator

---

## 📅 Notes
This project is implemented entirely in **C** using **doubly linked lists** and manual memory management. It's a practical exercise in:
- Linked list manipulation  
- Big number arithmetic  
- Handling signed numbers  
- Command-line argument parsing

If you want to extend this project, consider adding support for:
- Arbitrary-precision decimal numbers (fixed or arbitrary fractional part)  
- Exponentiation or modular arithmetic  
- A simple interactive REPL for multiple operations without restarting the program
