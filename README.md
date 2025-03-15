# ![QuarkNeo Logo](https://via.placeholder.com/150) <file:///C:/Users/Dell/Pictures/Screenshots/Screenshot%202025-03-15%20120133.png>

# Welcome To QuarkNeo Library 0.0.1

A Simplified C Library Empowering Beginners in Programming

**Author:** Aayush Badola  
**Version:** Initial  

---

## **Important**

Please update your library to the latest version to use it properly. This initial version is designed for educational purposes and simplifies C programming by providing intuitive functions inspired by Harvard's CS50 library but completely reimplemented.

---

## **Features**

- Simple input functions for various data types
- String type abstraction
- Error handling utilities
- Colored output functions for terminal applications
- Clean, well-documented codebase

---

## **Installation**

### **Building from Source**

git clone https://github.com/yourusername/quarkneo.git
cd quarkneo
make

text

### **Installing System-wide**

sudo make install

text

---

## **Using the Library**

### **Header File**

Include the header file in your C programs:

#include <quark.h>

text

*Note:* While the library is named QuarkNeo, we've kept the header file as `quark.h` for simplicity and compatibility.

### **Compilation**

Compile your program with the QuarkNeo library:

gcc -o myprogram myprogram.c -lquark

text

---

## **API Reference**

### **Input Functions**
- `char get_char(const char *prompt)` - Get a single character from user  
- `double get_double(const char *prompt)` - Get a double from user  
- `float get_float(const char *prompt)` - Get a float from user  
- `int get_int(const char *prompt)` - Get an integer from user  
- `long get_long(const char *prompt)` - Get a long integer from user  
- `string get_string(const char *prompt)` - Get a string from user  

### **Output Functions**
- `void print_red(const char *format, ...)` - Print text in red  
- `void print_green(const char *format, ...)` - Print text in green  
- `void print_yellow(const char *format, ...)` - Print text in yellow  
- `void print_blue(const char *format, ...)` - Print text in blue  

### **Error Handling**
- `void error(const char *format, ...)` - Print an error message and exit  

---

## **Example**

#include <quark.h>
#include <stdio.h>

int main(void)
{
string name = get_string("What is your name? ");
int age = get_int("How old are you? ");

text
print_green("Hello, %s! You are %d years old.\n", name, age);

// Remember to free memory allocated by get_string
free(name);

return 0;
}

text

---

## **Memory Management**

Remember that `get_string()` dynamically allocates memory for the string. You must call `free()` on the string when you're done using it to avoid memory leaks.

---

## **License**

This project is licensed under the MIT License.

---

## **Contributing**

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository  
2. Create your feature branch: `git checkout -b feature/amazing-feature`  
3. Commit your changes: `git commit -m 'Add some amazing feature'`  
4. Push to the branch: `git push origin feature/amazing-feature`  
5. Open a Pull Request  

---

## **Acknowledgments**

Inspired by Harvard's CS50 library but completely reimplemented for educational purposes. Designed to simplify learning C programming for beginners.
