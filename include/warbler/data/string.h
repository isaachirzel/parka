#ifndef WARBLER_STRING_H
#define WARBLER_STRING_H

// standard library
#include <stddef.h>

enum StringError
{
	STRING_MEMORY_ERROR,
	STRING_LENGTH_ERROR
};

typedef struct String
{
	const char *data;
	size_t length;
} String;

String string_default();

void string_print(const String *str);
void string_println(const String *str);
char *string_duplicate(const String *str);

#endif
