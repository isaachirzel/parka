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

void _errorf(const char *file, unsigned line, const char *func, const char *fmt, ...);
void _error(const char *file, unsigned line, const char *func, const char *msg);
void _errort(const char *file, unsigned line, const char *func, const char *msg, const Token *token);

void _debugf(const char *file, unsigned line, const char *func, const char *fmt, ...);
void _debug(const char *file, unsigned line, const char *func, const char *msg);

#define errorf(fmt, ...) _errorf(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
#define error(msg) _error(__FILE__, __LINE__, __func__, msg)
#define errort(msg, token) _errort(__FILE__, __LINE__, __func__, msg, token)

#ifndef NDEBUG
	#define debugf(fmt, ...) _debugf(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
	#define debug(msg) _debug(__FILE__, __LINE__, __func__, msg)
#else
	#define debugf(fmt, ...)
	#define debug(msg)
#endif

#endif
