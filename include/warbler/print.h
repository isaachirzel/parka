#ifndef WARBLER_PRINT_H
#define WARBLER_PRINT_H

// local headers
#include <warbler/token.h>

// standard headers
#include <stdbool.h>

void print_enable_color(bool enabled);
void print_branch(unsigned count);
void print_tree_branch_symbol(const char *symbol, unsigned depth);
void print_spaces(unsigned count);

void ftprintf(FILE *stream, const char *fmt, ...);
void tprintf(const char *fmt, ...);
void errortf(const Token *token, const char *fmt, ...);
void errort(const Token *token, const char *msg);
void errorm(const char *msg);
void errorf(const char *fmt, ...);

void _debugf(const char *file, unsigned line, const char *func, const char *fmt, ...);
void _debug(const char *file, unsigned line, const char *func, const char *msg);

#ifndef NDEBUG
	#define debugf(fmt, ...) _debugf(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
	#define debug(msg) _debug(__FILE__, __LINE__, __func__, msg)
#else
	#define debugf(fmt, ...)
	#define debug(msg)
#endif

#endif
