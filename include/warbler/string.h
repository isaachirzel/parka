#ifndef WARBLER_DATA_STRING_H
#define WARBLER_DATA_STRING_H

// standard
#include <stddef.h>

typedef struct String
{
	const char *data;
	size_t length;
} String;

String string_default();
String string_from(const char *text);

void string_print(const String *str);
void string_println(const String *str);
char *string_duplicate(const String *str);
#define STRING_FROM(text) (String) { .data = text, .length = sizeof(text) - 1 }

#endif
