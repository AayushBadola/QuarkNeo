#include "quark.h"
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

void error(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(1);
}

string get_string(const char *prompt) {
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }

    size_t capacity = 16;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        error("Memory allocation failed");
    }

    size_t size = 0;
    int c;

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (size + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                 free(buffer);
                 error("Memory allocation failed (capacity overflow)");
            }
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                error("Memory allocation failed");
            }
            buffer = new_buffer;
        }
        buffer[size++] = (char)c;
    }

    if (size == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';

    return buffer;
}


char get_char(const char *prompt) {
    string input = get_string(prompt);
    if (input == NULL) {
        error("Failed to read input from stdin");
    }

    if (input[0] == '\0' || input[1] != '\0') {
         free(input);
         error("Expected a single character");
    }

    char c = input[0];
    free(input);
    return c;
}


static bool parse_numeric(const char *input, const char *format, void *result) {
    if (input == NULL || input[0] == '\0') {
        return false;
    }

    char *end;
    errno = 0;

    if (strcmp(format, "%d") == 0) {
        long l = strtol(input, &end, 10);
        if (end == input || *end != '\0' || ((errno == ERANGE && (l == LONG_MAX || l == LONG_MIN)) || l > INT_MAX || l < INT_MIN)) {
            return false;
        }
        *(int *)result = (int)l;
    } else if (strcmp(format, "%ld") == 0) {
        long l = strtol(input, &end, 10);
        if (end == input || *end != '\0' || (errno == ERANGE && (l == LONG_MAX || l == LONG_MIN))) {
            return false;
        }
        *(long *)result = l;
    } else if (strcmp(format, "%f") == 0) {
        float f = strtof(input, &end);
        if (end == input || *end != '\0' || errno == ERANGE) {
             // Allow for inf/-inf? For now, strtof handles range correctly, check errno.
            return false;
        }
        *(float *)result = f;
    } else if (strcmp(format, "%lf") == 0) {
        double d = strtod(input, &end);
        if (end == input || *end != '\0' || errno == ERANGE) {
            // Allow for inf/-inf? For now, strtod handles range correctly, check errno.
            return false;
        }
        *(double *)result = d;
    } else {
        return false;
    }

    return true;
}


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
        printf("Invalid input. Please enter an integer.\n");
        if (prompt != NULL) {
             printf("%s", prompt);
             fflush(stdout);
        }
    }
}


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
        printf("Invalid input. Please enter a long integer.\n");
        if (prompt != NULL) {
             printf("%s", prompt);
             fflush(stdout);
        }
    }
}


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
        printf("Invalid input. Please enter a float.\n");
         if (prompt != NULL) {
             printf("%s", prompt);
             fflush(stdout);
         }
    }
}


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
        printf("Invalid input. Please enter a double.\n");
        if (prompt != NULL) {
             printf("%s", prompt);
             fflush(stdout);
        }
    }
}


void print_red(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_RED);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}


void print_green(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_GREEN);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}


void print_yellow(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_YELLOW);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}


void print_blue(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf(COLOR_BLUE);
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}
