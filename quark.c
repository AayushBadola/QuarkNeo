/**
 * Quark.c
 *
 * Implementation of the Quark library functions.
 */

#include "quark.h"
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Include for INT_MAX and INT_MIN

// ANSI color codes
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

/**
 * Prints an error message, formatted like printf, to standard error and exits with code 1.
 */
void error(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(1);
}

/**
 * Reads a line of text from standard input and returns it as a string.
 * Memory is allocated for the string and must be freed by the caller.
 */
string get_string(const char *prompt) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }

    // Allocate buffer with initial capacity
    size_t capacity = 16;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        error("Memory allocation failed");
        return NULL;
    }

    size_t size = 0;
    int c;

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        // Resize buffer if necessary
        if (size + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                error("Memory allocation failed");
                return NULL;
            }
            buffer = new_buffer;
        }

        // Append character to buffer
        buffer[size++] = c;
    }

    if (size == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    // Terminate string
    buffer[size] = '\0';

    // Shrink buffer to minimum size needed
    char *minimal = realloc(buffer, size + 1);
    return minimal != NULL ? minimal : buffer; // Returns original buffer on failure, as realloc specifies
}

/**
 * Reads a char from standard input and returns it.
 */
char get_char(const char *prompt) {
    string input = get_string(prompt);
    if (input == NULL) {
        error("Failed to read input from stdin");
    }

    if (strlen(input) != 1) {
        free(input);
        error("Expected a single character");
    }

    char c = input[0];
    free(input);
    return c;
}

/**
 * Helper function to parse numeric input with validation
 */
static bool parse_numeric(const char *input, const char *format, void *result) {
    // Check for empty string
    if (strlen(input) == 0) {
        return false;
    }

    // Check for non-numeric characters (allowing for decimal point and sign)
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && input[i] != '.' && input[i] != '-' && input[i] != '+') {
            return false;
        }
    }

    // Try to parse
    char *end;
    errno = 0;

    if (strcmp(format, "%d") == 0) {
        long l = strtol(input, &end, 10);
        if (end == input || *end != '\0' || errno == ERANGE || l > INT_MAX || l < INT_MIN) {
            return false;
        }
        *(int *)result = (int)l;
    } else if (strcmp(format, "%ld") == 0) {
        long l = strtol(input, &end, 10);
        if (end == input || *end != '\0' || errno == ERANGE) {
            return false;
        }
        *(long *)result = l;
    } else if (strcmp(format, "%f") == 0) {
        float f = strtof(input, &end);
        if (end == input || *end != '\0' || errno == ERANGE) {
            return false;
        }
        *(float *)result = f;
    } else if (strcmp(format, "%lf") == 0) {
        double d = strtod(input, &end);
        if (end == input || *end != '\0' || errno == ERANGE) {
            return false;
        }
        *(double *)result = d;
    } else {
        return false;
    }

    return true;
}

/**
 * Gets an int from standard input
 */
int get_int(const char *prompt) {
    while (true) {
        string input = get_string(prompt);
        if (input == NULL) {
            error("Failed to read input");
        }

        int value;
        if (parse_numeric(input, "%d", &value)) {
            free(input);
            return value;
        }

        free(input);
        printf("Invalid input. Please enter an integer: %s", prompt != NULL ? "" : "");
    }
}

/**
 * Gets a long from standard input
 */
long get_long(const char *prompt) {
    while (true) {
        string input = get_string(prompt);
        if (input == NULL) {
            error("Failed to read input");
        }

        long value;
        if (parse_numeric(input, "%ld", &value)) {
            free(input);
            return value;
        }

        free(input);
        printf("Invalid input. Please enter a long integer: %s", prompt != NULL ? "" : "");
    }
}

/**
 * Gets a float from standard input
 */
float get_float(const char *prompt) {
    while (true) {
        string input = get_string(prompt);
        if (input == NULL) {
            error("Failed to read input");
        }

        float value;
        if (parse_numeric(input, "%f", &value)) {
            free(input);
            return value;
        }

        free(input);
        printf("Invalid input. Please enter a float: %s", prompt != NULL ? "" : "");
    }
}

/**
 * Gets a double from standard input
 */
double get_double(const char *prompt) {
    while (true) {
        string input = get_string(prompt);
        if (input == NULL) {
            error("Failed to read input");
        }

        double value;
        if (parse_numeric(input, "%lf", &value)) {
            free(input);
            return value;
        }

        free(input);
        printf("Invalid input. Please enter a double: %s", prompt != NULL ? "" : "");
    }
}

/**
 * Print in red color
 */
void print_red(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_RED);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}

/**
 * Print in green color
 */
void print_green(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_GREEN);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}

/**
 * Print in yellow color
 */
void print_yellow(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_YELLOW);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}

/**
 * Print in blue color
 */
void print_blue(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_BLUE);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}
