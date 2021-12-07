#ifndef WARBLER_ERROR_H
#define WARBLER_ERROR_H

#include <stdlib.h>
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
	ERROR_INVALID_PTR
} Error;

#define not_implemented_error() print_errorf("%s is not implemented yet", __func__); abort()

extern bool is_color_output;
extern void print_error(const char *msg);
extern void print_errorf(const char *fmt, ...);
#define try(expression) { Error error = expression; if (error) return error; }

#endif
