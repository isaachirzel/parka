#ifndef WARBLER_ERROR_H
#define WARBLER_ERROR_H

// local headers
#include <warbler/token.h>

// standard headers
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef enum Error
{
	ERROR_NONE,
	ERROR_MEMORY,
	ERROR_ARGUMENT,
	ERROR_FILE,
	ERROR_PARSE,
	ERROR_NOT_FOUND,
	ERROR_INVALID_PTR,
	ERROR_NOT_IMPLEMENTED
} Error;

static inline Error _not_implemented_error(const char *func_name)
{
	fprintf(stderr, "\033[31mnot implemented:\033[0m %s()\n", func_name);
	return ERROR_NOT_IMPLEMENTED;
}

#define try(expr) { Error error = expr; if (error) return error; }
#define not_implemented_error() _not_implemented_error(__func__);

#endif
