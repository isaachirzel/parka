#ifndef STRING_H
#define STRING_H

// standard library
#include <stdio.h>

typedef struct string
{
	const char *ptr;
	unsigned len;
} string_t;

void string_print(string_t str);
void string_put(string_t str);
void string_fputs(string_t str, FILE *stream);
char *string_duplicate(string_t *str);

#endif
