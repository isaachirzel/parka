#include <warbler/data/string.h>

// local includes
#include <warbler/error.h>

// standard library
#include <stdio.h>
#include <stdlib.h>

void String_print(const String *str)
{
	fwrite(str->start, sizeof(char), str->end - str->start, stdout);	
}

void String_println(const String *str)
{
	String_print(str);
	putchar('\n');
}

char *String_duplicate(const String *str)
{
	size_t size = str->end - str->start;

	if (size == 0)
	{
		print_errorf("%s: attempted to duplicate string with length 0", __func__);
		return NULL;
	}
	
	char *out = malloc((size + 1) * sizeof(char));

	if (!out)
	{
		print_errorf("%s: failed to allocate string buffer", __func__);
		return NULL;
	}

	for (size_t i = 0; i < size; ++i)
	{
		out[i] = str->start[i];
	}

	out[size] = 0;

	return out;
}
