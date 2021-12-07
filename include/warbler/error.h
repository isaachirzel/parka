#ifndef WARBLER_ERROR_H
#define WARBLER_ERROR_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum ErrorType
{
	ERROR_NO_MEMORY,
	ERROR_BAD_ARGUMENT
} ErrorType;

#define not_implemented_error() print_errorf("%s is not implemented yet", __func__); abort()

extern bool is_color_output;
extern void print_error(const char *msg);
extern void print_errorf(const char *fmt, ...);

#endif
