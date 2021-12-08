#ifndef WARBLER_ERROR_H
#define WARBLER_ERROR_H

// standard
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

typedef enum Error
{
	ERROR_NONE = 0,
	ERROR_MEMORY,
	ERROR_FILE,
	ERROR_ARGUMENT,
	ERROR_NOT_FOUND,
	ERROR_INVALID_PTR,
	ERROR_NOT_IMPLEMENTED
} Error;

extern bool is_color_enabled;
extern bool is_printing_enabled;

void print_error(const char *msg);
void print_errorf(const char *fmt, ...);
void set_color_enabled(bool enabled);
void set_printing_enabled(bool enabled);

static inline Error _not_implemented_error(const char *func_name)
{
	print_errorf("%s is not implemented yet", func_name);
	return ERROR_NOT_IMPLEMENTED;
}

#define not_implemented_error() _not_implemented_error(__func__);
#define try(expression) { Error error = expression; if (error) return error; }
#define try_allocate(var) { var = malloc(sizeof(*var)); if (!var) return ERROR_MEMORY; }
#define try_cleanup(expression, catch_statement) { Error error = expression; if (error) { catch_statement return error; } }

#endif
