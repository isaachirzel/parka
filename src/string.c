#include <grackle/string.h>

// standard library
#include <stdio.h>

void string_print(string_t str)
{
	for (unsigned i = 0; i < str.len; ++i)
	{
		putchar(str.ptr[i]);
	}
}


void string_put(string_t str)
{
	string_print(str);
	putchar('\n');
}
