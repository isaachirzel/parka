#ifndef STRING_H
#define STRING_H

// standard library
#include <stdio.h>

typedef struct string
{
	const char *ptr;
	unsigned len;
} string_t;

void string_print(const string_t *str);
void string_put(const string_t *str);
void string_fputs(const string_t *str, FILE *stream);
char *string_duplicate(const string_t *str);

#endif
