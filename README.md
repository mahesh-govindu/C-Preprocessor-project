# C-Preprocessor-project
# Preprocessor

## Project Overview

The **Preprocessor** project is a C-based tool named `mypreprocessor`.
It processes a C source file by performing comment removal, file
inclusion, and macro substitution. The processed output is generated as
a file with the `.i` extension.

## Objective

Develop a preprocessor tool that accepts a C source filename through
command-line arguments and creates an extended source file after
processing it.

## Features

### 1. Comment Removal

-   Identifies and removes single-line comments beginning with `//`.
-   Identifies and removes multi-line comments enclosed between `/*` and
    `*/`.
-   Preserves the structure and readability of the remaining code.

### 2. File Inclusion

-   Detects lines containing `#include <filename>`.
-   Opens the specified file.
-   Replaces the `#include` line in the output with the contents of the
    included file.

### 3. Macro Substitution

-   Detects `#define` directives and stores macro definitions.

-   Replaces subsequent macro usages with their corresponding defined
    values.

-   Supports simple macros, for example:

    ``` c
    #define PI 3.14
    ```

-   Supports macros with arguments, for example:

    ``` c
    #define SQUARE(x) ((x)*(x))
    ```

## Project Requirements

-   The program must be compiled into an executable named
    `mypreprocessor`.
-   The input filename must be supplied through command-line arguments.
-   The processed output must be created with the `.i` extension.
-   The project must use modular programming, with functionality divided
    across multiple `.c` and `.h` files.
-   A `Makefile` must be provided to compile all modules and create the
    `mypreprocessor` executable.

## Project Structure

An example modular structure is:

``` text
PREPROCESSOR/
├── README.md
├── Makefile
├── main.c
├── comment_.c
├── comment.h
├── header.c
├── header.h
├── macro.c
└── macro.h
```

The filenames above are examples of the suggested module organization.

## Compilation

Build the project using:

``` bash
make
```

This should compile the modules and generate the executable:

``` text
mypreprocessor
```

## Usage

Run the program by passing a C source file as a command-line argument:

``` bash
./mypreprocessor inputfile.c
```

After processing, the program should create:

``` text
inputfile.i
```

## Technologies and Concepts

-   C programming
-   Command-line arguments
-   File handling
-   Preprocessor directives
-   Modular programming
-   Makefile

