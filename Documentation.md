# QuarkNeo Library - Complete Documentation

## Table of Contents
1. [Introduction](#introduction)
2. [Library Architecture](#library-architecture)
3. [API Reference](#api-reference)
4. [Implementation Details](#implementation-details)
5. [Memory Management](#memory-management)
6. [Thread Safety](#thread-safety)
7. [Error Handling](#error-handling)
8. [Performance Considerations](#performance-considerations)
9. [Building and Integration](#building-and-integration)
10. [Examples](#examples)
11. [Contribution Guidelines](#contribution-guidelines)
12. [Version History](#version-history)

---

## Introduction

QuarkNeo is a lightweight, educational C library inspired by Harvard's CS50 library but completely reimplemented from scratch. It provides simplified functions for common operations in C programming, with a focus on making C more approachable for beginners while maintaining good programming practices.

### Design Philosophy

The QuarkNeo library follows several key design principles:
- **Simplicity**: Functions are designed with clear, intuitive interfaces
- **Safety**: Input validation and error checking are built into the core functions
- **Educational value**: Code is thoroughly commented and structured for learning
- **Minimal dependencies**: Only relies on the C standard library

---

## Library Architecture

QuarkNeo follows a modular design with distinct functional categories:

### Component Overview
- **Input Processing**: Functions to safely retrieve various data types from stdin
- **Output Formatting**: Functions for colored terminal output
- **Error Handling**: Centralized error reporting system

### File Structure
- `quark.h`: Public interface declaration
- `quark.c`: Implementation of all library functions

---

## API Reference

### Data Types

| Type | Description |
|------|-------------|
| `string` | Type alias for `char*`, representing dynamically allocated strings |

### Input Functions

#### `char get_char(const char *prompt)`
Gets a single character from standard input.

**Parameters:**
- `prompt`: Optional text prompt to display (can be NULL)

**Returns:**
- The character entered by the user

**Example:**
```c
char answer = get_char("Continue? (y/n): ");
if (answer == 'y') {
    // Process confirmation
}
```

#### `int get_int(const char *prompt)`
Gets an integer from standard input with validation.

**Parameters:**
- `prompt`: Optional text prompt to display (can be NULL)

**Returns:**
- The validated integer entered by the user

**Error Handling:**
- Re-prompts if input is not a valid integer
- Checks for integer overflow/underflow

**Example:**
```c
int age = get_int("How old are you? ");
```

#### `long get_long(const char *prompt)`
Gets a long integer from standard input with validation.

**Parameters:**
- `prompt`: Optional text prompt to display (can be NULL)

**Returns:**
- The validated long integer entered by the user

**Error Handling:**
- Re-prompts if input is not a valid long integer
- Checks for overflow/underflow

**Example:**
```c
long population = get_long("Enter world population: ");
```

#### `float get_float(const char *prompt)`
Gets a floating-point number from standard input with validation.

**Parameters:**
- `prompt`: Optional text prompt to display (can be NULL)

**Returns:**
- The validated float entered by the user

**Error Handling:**
- Re-prompts if input is not a valid float
- Checks for overflow/underflow

**Example:**
```c
float temperature = get_float("Current temperature: ");
```

#### `double get_double(const char *prompt)`
Gets a double-precision floating-point number from standard input with validation.

**Parameters:**
- `prompt`: Optional text prompt to display (can be NULL)

**Returns:**
- The validated double entered by the user

**Error Handling:**
- Re-prompts if input is not a valid double
- Checks for overflow/underflow

**Example:**
```c
double precise_measurement = get_double("Enter measurement (in mm): ");
```

#### `string get_string(const char *prompt)`
Gets a line of text from standard input.

**Parameters:**
- `prompt`: Optional text prompt to display (can be NULL)

**Returns:**
- Dynamically allocated string containing the input (must be freed by caller)
- NULL if memory allocation fails or EOF is reached

**Memory Management:**
- Caller must free the returned string with `free()`
- Dynamic resizing is handled internally

**Example:**
```c
string name = get_string("What is your name? ");
if (name != NULL) {
    printf("Hello, %s!\n", name);
    free(name);  // Important: free the allocated memory
}
```

### Output Functions

#### `void print_red(const char *format, ...)`
Prints text in red color to standard output.

**Parameters:**
- `format`: printf-style format string
- `...`: Variable arguments for the format string

**Example:**
```c
print_red("Error: %s not found.\n", filename);
```

#### `void print_green(const char *format, ...)`
Prints text in green color to standard output.

**Parameters:**
- `format`: printf-style format string
- `...`: Variable arguments for the format string

**Example:**
```c
print_green("Success! File %s created.\n", filename);
```

#### `void print_yellow(const char *format, ...)`
Prints text in yellow color to standard output.

**Parameters:**
- `format`: printf-style format string
- `...`: Variable arguments for the format string

**Example:**
```c
print_yellow("Warning: Low disk space (%d%% remaining).\n", percentage);
```

#### `void print_blue(const char *format, ...)`
Prints text in blue color to standard output.

**Parameters:**
- `format`: printf-style format string
- `...`: Variable arguments for the format string

**Example:**
```c
print_blue("Info: Processing file %d of %d.\n", current, total);
```

### Error Handling

#### `void error(const char *format, ...)`
Prints an error message to stderr and exits the program.

**Parameters:**
- `format`: printf-style format string
- `...`: Variable arguments for the format string

**Behavior:**
- Prefixes the message with "Error: "
- Outputs to stderr
- Terminates program with exit code 1

**Example:**
```c
if (file == NULL) {
    error("Could not open file %s", filename);
}
```

---

## Implementation Details

### Input Processing

The input functions follow a consistent pattern:
1. Display prompt if provided
2. Read input from stdin
3. Validate input based on the expected type
4. Re-prompt if validation fails
5. Return the validated value

#### String Input Implementation

The `get_string()` function uses a dynamic buffer approach:
1. Starts with a reasonably sized buffer (16 bytes)
2. Reads characters one at a time
3. Doubles buffer size when needed
4. Terminates the string with null character
5. Resizes buffer to exact size needed before returning

#### Numeric Input Validation

Numeric input functions use a common helper function `parse_numeric()` that:
1. Checks for empty input
2. Validates that all characters are valid for the data type
3. Uses appropriate `strtol`, `strtof`, or `strtod` functions
4. Checks for parsing errors and range violations
5. Stores the result in the provided output parameter

### Color Output Implementation

The color output functions use ANSI escape sequences:
1. Set the appropriate color code using `printf(COLOR_X)`
2. Output the formatted string using `vprintf()`
3. Reset color to default using `printf(COLOR_RESET)`

---

## Memory Management

### Dynamic Allocation

The QuarkNeo library uses dynamic memory allocation in the following functions:
- `get_string()`: Allocates memory for the returned string

### Memory Responsibility

All memory allocated by `get_string()` must be freed by the caller. Failure to do so will result in memory leaks.

### Internal Memory Handling

Internally, the library follows these memory management practices:
- Initial allocation with reasonable buffer size
- Doubling strategy for buffer growth
- Final reallocation to minimize memory waste
- Proper error handling for allocation failures
- Cleanup of temporary resources

---

## Thread Safety

The current implementation of QuarkNeo is not explicitly thread-safe. Considerations when using in multi-threaded environments:

- The input functions manipulate stdin, which is shared across threads
- The output functions manipulate stdout/stderr, which are shared across threads
- No internal state is maintained between function calls
- No static or global variables are used that would create race conditions

For thread-safe usage, consider:
- Using mutex locks around function calls
- Not calling the same input functions from multiple threads simultaneously
- Using thread-local buffers for processing input/output

---

## Error Handling

### Error Categories

The library handles several types of errors:
1. **Input validation errors**: Invalid data entered by user
2. **Memory allocation failures**: When system cannot allocate memory
3. **Fatal errors**: Conditions that prevent program continuation

### Error Handling Approaches

Different approaches are used based on error category:
- **Input validation errors**: Re-prompt the user
- **Memory allocation failures**: Call error() function which terminates program
- **Fatal errors**: Call error() function which terminates program

---

## Performance Considerations

### Input Processing

- String input uses dynamic reallocation which may have performance implications for very long inputs
- Numeric input validation involves multiple passes over input data
- Re-prompting for invalid input adds user interaction overhead

### Optimization Opportunities

- Buffer size growth strategy could be tuned for specific use cases
- Input validation could be optimized for common patterns
- Specialized versions could be added for performance-critical scenarios

---

## Building and Integration

### Building the Library

QuarkNeo can be built as a static library using the provided Makefile:

```bash
make
```

This produces `libquark.a` which can be linked with your applications.

### Linking with Applications

To link QuarkNeo with your application:

```bash
gcc -o myprogram myprogram.c -L/path/to/quarkneo -lquark
```

### Installation

To install system-wide:

```bash
sudo make install
```

This copies the library to `/usr/local/lib` and headers to `/usr/local/include`.

### Integration with Build Systems

#### CMake Integration

```cmake
# In your CMakeLists.txt
find_library(QUARK_LIBRARY NAMES quark)
find_path(QUARK_INCLUDE_DIR NAMES quark.h)

add_executable(myapp main.c)
target_include_directories(myapp PRIVATE ${QUARK_INCLUDE_DIR})
target_link_libraries(myapp ${QUARK_LIBRARY})
```

---

## Examples

### Basic Input/Output Example

```c
#include <quark.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name? ");
    int age = get_int("How old are you? ");
    
    print_green("Hello, %s! ", name);
    printf("You are %d years old.\n", age);
    
    free(name);
    return 0;
}
```

### Input Validation Example

```c
#include <quark.h>
#include <stdio.h>

int main(void)
{
    // Will keep prompting until valid integer is entered
    int positive_number = get_int("Enter a positive number: ");
    
    while (positive_number <= 0) {
        print_yellow("Please enter a positive number!\n");
        positive_number = get_int("Enter a positive number: ");
    }
    
    printf("You entered: %d\n", positive_number);
    return 0;
}
```

### Error Handling Example

```c
#include <quark.h>
#include <stdio.h>

int main(void)
{
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        error("Could not open file 'nonexistent.txt'");
        // Program terminates here
    }
    
    // Code below won't execute if file can't be opened
    fclose(file);
    return 0;
}
```

---

## Contribution Guidelines

### Coding Standards

- Follow C11 standard
- Use consistent indentation (4 spaces)
- Add comprehensive comments
- Follow function naming conventions
- Include error handling for all functions

### Pull Request Process

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass
6. Submit pull request with detailed description

### Documentation Updates

When adding or modifying functionality, be sure to:
- Update function documentation
- Add examples for new functions
- Update this comprehensive documentation

---

## Version History

### v1.0.0 (Initial Release)
- Basic input functions (get_char, get_int, get_long, get_float, get_double, get_string)
- Color output functions (print_red, print_green, print_yellow, print_blue)
- Error handling function (error)
- Complete documentation and examples
  
