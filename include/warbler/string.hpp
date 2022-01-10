#ifndef WARBLER_DATA_STRING_HPP
#define WARBLER_DATA_STRING_HPP

// standard
#include <stddef.h>
#include <stdio.h>
namespace warbler
{
	struct String
	{
		const char *data;
		size_t length;
	};

	String string_default();
	String string_from(const char *text);

	void string_print(const String *str);
	void string_fprint(const String *string, FILE *stream);
	void string_println(const String *str);
	char *string_duplicate(const String *str);
}
#define STRING_FROM(text) (String) { .data = text, .length = sizeof(text) - 1 }

#endif
