# Toy Compiler / Interpreter in C++

> A small expression language implemented end-to-end in C++: lexer → parser → AST → tree-walking interpreter.

This project implements a **minimal interpreted language** to explore how real compilers and interpreters work internally, with a focus on **core C++ systems concepts** rather than features or performance optimisations.

---

## What this project is

- A **handwritten lexer** that converts source code into tokens
- A **recursive-descent parser** that builds an Abstract Syntax Tree (AST)
- A **tree-walking interpreter (executor)** that evaluates the AST
- A simple **runtime environment** for variables

The language supports:
- integer arithmetic (`+ - * /`)
- parentheses and operator precedence
- variable assignment
- `print` statements
  
## Project motivation

This project was built as a learning exercise to deeply understand:

- how parsers build structure
- how Abstract Syntax Trees (ASTs) represent programs
- how interpreters traverse trees
- ho


Example program:
```text
x = 3 + 4 * (2 - 1)
print x
```
Output:
```
7
```
## Key concepts demonstrated

This project was built specifically to practice and understand:

### Language & syntax
- Recursive-descent parsing
- Operator precedence handling
- Abstract Syntax Tree (AST) construction

### C++ core concepts
- RAII and ownership
- `std::unique_ptr` for AST lifetime management
- Move semantics (`std::move`)
- References vs pointers
- `const` correctness
- Header / source separation
- Encapsulation (private parser helpers)

### Polymorphism & runtime behaviour
- Virtual destructors for AST base classes
- Runtime dispatch (`dynamic_cast`) in the executor
- Tree traversal via recursion
---

## Design decisions (intentional)

- No parser generators (e.g. yacc / bison)
- No LLVM or bytecode backend
- No garbage collection
- No copyable AST nodes


