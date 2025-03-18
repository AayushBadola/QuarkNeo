/**
 * Quark.c
 *
 * Implementation of the Quark library.
 *
 * MIT Copyright (c) 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>  // For variable arguments
#include "Quark.h"    // IMPORTANT: Use "" because it's a local header.

// ----------------------- Input Functions -----------------------

char get_char(const char *prompt) {
    printf("%s", prompt);
    int c = getchar();
    while (getchar() != '\n');  // Clear the input buffer. Prevents errors.
    return (char)c;
}

double get_double(const char *prompt) {
    double value;
    printf("%s", prompt);
    if (scanf("%lf", &value) != 1) {
        error("Invalid double input.");
    }
    while (getchar() != '\n'); // Clear buffer
    return value;
}

float get_float(const char *prompt) {
    float value;
    printf("%s", prompt);
    if (scanf("%f", &value) != 1) {
        error("Invalid float input.");
    }
    while (getchar() != '\n'); // Clear buffer
    return value;
}

int get_int(const char *prompt) {
    int value;
    printf("%s", prompt);
    if (scanf("%d", &value) != 1) {
        error("Invalid integer input.");
    }
    while (getchar() != '\n'); // Clear buffer
    return value;
}

long get_long(const char *prompt) {
    long value;
    printf("%s", prompt);
    if (scanf("%ld", &value) != 1) {
        error("Invalid long integer input.");
    }
    while (getchar() != '\n'); // Clear buffer
    return value;
}


string get_string(const char *prompt) {
    char buffer[256]; // Arbitrary buffer size.  Consider dynamically allocating for safety.
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove trailing newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        string str = strdup(buffer);  // Allocate memory for the string. IMPORTANT: Caller MUST free this.
        if (str == NULL) {
            error("Memory allocation failed in get_string.");
        }
        return str;
    } else {
        error("Error reading string input.");
        return NULL;  // Should not reach here because error() exits.
    }
}


// ----------------------- Error Handling -----------------------

void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}


// ----------------------- Color Output (Basic Example) -----------------------

// Note:  These are very basic.  A more robust solution would handle
// terminal capabilities and allow for more complex color schemes.
// These escape codes might not work on all terminals.

void print_red(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[0;31m");  // Red color code
    vprintf(format, args);
    printf("\033[0m");     // Reset to default color
    va_end(args);
}

void print_green(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[0;32m");  // Green color code
    vprintf(format, args);
    printf("\033[0m");     // Reset to default color
    va_end(args);
}

void print_yellow(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[0;33m");  // Yellow color code
    vprintf(format, args);
    printf("\033[0m");     // Reset to default color
    va_end(args);
}

void print_blue(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[0;34m");  // Blue color code
    vprintf(format, args);
    printf("\033[0m");     // Reset to default color
    va_end(args);
}
