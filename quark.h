/**
 * Quark.h
 *
 * A simplified library for C programming designed for educational purposes,
 * inspired by Harvard's CS50 library but completely reimplemented.
 *
 * Copyright (c) 2025
 */

#ifndef QUARK_H
#define QUARK_H

#include <stdbool.h>
#include <stddef.h>

/**
 * String type for simplicity
 */
typedef char *string;

/**
 * Function prototypes for getting input
 */
char get_char(const char *prompt);
double get_double(const char *prompt);
float get_float(const char *prompt);
int get_int(const char *prompt);
long get_long(const char *prompt);
string get_string(const char *prompt);

/**
 * Prints a formatted error message to stderr and exits
 */
void error(const char *format, ...);

/**
 * Function prototypes for color output
 */
void print_red(const char *format, ...);
void print_green(const char *format, ...);
void print_yellow(const char *format, ...);
void print_blue(const char *format, ...);

#endif // QUARK_H
