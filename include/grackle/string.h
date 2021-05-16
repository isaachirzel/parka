#ifndef STRING_H
#define STRING_H

typedef struct string
{
	const char *ptr;
	unsigned len;
} string_t;

void string_print(string_t str);

#endif
