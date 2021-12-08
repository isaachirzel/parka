#ifndef WARBLER_ERROR_H
#define WARBLER_ERROR_H

// standard
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

typedef enum Error
{
	ERROR_NONE,
	ERROR_MEMORY,
	ERROR_FILE,
	ERROR_ARGUMENT,
	ERROR_NOT_FOUND,
	ERROR_INVALID_PTR,
	ERROR_NOT_IMPLEMENTED
} Error;

extern bool is_color_output;
extern void print_error(const char *msg);
extern void print_errorf(const char *fmt, ...);

static inline Error _not_implemented_error(const char *func_name)
{
	print_errorf("%s is not implemented yet", func_name);
	return ERROR_NOT_IMPLEMENTED;
}

#define try(expression) { Error error = expression; if (error) return error; }
#define not_implemented_error() _not_implemented_error(__func__);

#endif
