#ifndef QUARK_H
#define QUARK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdnoreturn.h> // For noreturn attribute

// Define attribute macros for cross-compiler compatibility (basic)
#if defined(__GNUC__) || defined(__clang__)
    #define QUARK_PRINTF_FORMAT(fmt_idx, arg_idx) __attribute__((__format__ (__printf__, fmt_idx, arg_idx)))
    #define QUARK_NORETURN _Noreturn // C11 standard, supported by GCC/Clang
#else
    #define QUARK_PRINTF_FORMAT(fmt_idx, arg_idx)
    #define QUARK_NORETURN // Define as empty if not supported or needed
#endif


#ifdef __cplusplus
extern "C" {
#endif


typedef char *string;


noreturn void error(const char *format, ...) QUARK_PRINTF_FORMAT(1, 2);


string get_string(const char *prompt);
char get_char(const char *prompt);
int get_int(const char *prompt);
long get_long(const char *prompt);
float get_float(const char *prompt);
double get_double(const char *prompt);


void print_red(const char *format, ...) QUARK_PRINTF_FORMAT(1, 2);
void print_green(const char *format, ...) QUARK_PRINTF_FORMAT(1, 2);
void print_yellow(const char *format, ...) QUARK_PRINTF_FORMAT(1, 2);
void print_blue(const char *format, ...) QUARK_PRINTF_FORMAT(1, 2);


#ifdef __cplusplus
}
#endif

#endif // QUARK_H
