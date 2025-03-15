# QuarkNeo Library

The QuarkNeo Library is a simplified C library designed for educational purposes, inspired by Harvard's CS50 library but completely reimplemented. It provides intuitive functions for common operations in C programming, making it easier for beginners to learn and write C code.

## Features

- Simple input functions for various data types
- String type abstraction
- Error handling utilities
- Colored output functions for terminal applications
- Clean, well-documented codebase

## Installation

### Building from Source

```bash
git clone https://github.com/yourusername/quarkneo.git
cd quarkneo
make
```

### Installing System-wide

```bash
sudo make install
```

## Using the Library

### Header File

Include the header file in your C programs:

```c
#include <quark.h>
```

Note: While the library is named QuarkNeo, we've kept the header file as `quark.h` for simplicity and compatibility.

### Compilation

Compile your program with the QuarkNeo library:

```bash
gcc -o myprogram myprogram.c -lquark
```

## API Reference

### Input Functions

- `char get_char(const char *prompt)` - Get a single character from user
- `double get_double(const char *prompt)` - Get a double from user
- `float get_float(const char *prompt)` - Get a float from user
- `int get_int(const char *prompt)` - Get an integer from user
- `long get_long(const char *prompt)` - Get a long integer from user
- `string get_string(const char *prompt)` - Get a string from user

### Output Functions

- `void print_red(const char *format, ...)` - Print text in red
- `void print_green(const char *format, ...)` - Print text in green
- `void print_yellow(const char *format, ...)` - Print text in yellow
- `void print_blue(const char *format, ...)` - Print text in blue

### Error Handling

- `void error(const char *format, ...)` - Print an error message and exit

## Example

```c
#include <quark.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name? ");
    int age = get_int("How old are you? ");
    
    print_green("Hello, %s! You are %d years old.\n", name, age);
    
    // Remember to free memory allocated by get_string
    free(name);
    
    return 0;
}
```

## Memory Management

Remember that `get_string()` dynamically allocates memory for the string. You must call `free()` on the string when you're done using it to avoid memory leaks.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch: `git checkout -b feature/amazing-feature`
3. Commit your changes: `git commit -m 'Add some amazing feature'`
4. Push to the branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

## Acknowledgments

- Inspired by Harvard's CS50 library, but completely reimplemented
- Designed for educational purposes to simplify learning C programming
