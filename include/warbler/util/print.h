#ifndef WARBLER_UTIL_PRINT_H
#define WARBLER_UTIL_PRINT_H

// local headers
#include <warbler/token.h>
#include <warbler/snippet.h>
#include <stdnoreturn.h>

noreturn void _exitWithError(const char *file, usize line, const char *fmt, ...);
#define exitWithError(fmt, ...) _exitWithError(__FILE__, __LINE__, fmt, __VA_ARGS__)

noreturn void _exitNotImplemented(const char *file, usize line, const char *func);
#define exitNotImplemented() _exitNotImplemented(__FILE__, __LINE__, __func__)

void enableColorPrinting(bool enabled);

void _print(const char *file, u32 line, const char *msg);
#define print(msg) _print(__FILE__, __LINE__, msg)

// void printNote(const Snippet *text, const String *msg);
// void printWarning(const Snippet *text, const String *msg);
// void printError(const Snippet *text, const String *msg);

void printTokenNote(const Token *token, const char *format, ...);
void printTokenWarning(const Token *token, const char *format, ...);
void printTokenError(const Token *token, const char *format, ...);

void printNote(const char *format, ...);
void printWarning(const char *format, ...);
void printError(const char *format, ...);

void printParseError(const Token *token, const char *expected, const char *message);

#endif
