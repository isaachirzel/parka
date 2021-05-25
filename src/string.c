#include <grackle/string.h>


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

void string_fputs(string_t str, FILE *stream)
{
	for (size_t i = 0; i < str.len; ++i)
	{
		fputc(str.ptr[i], stream);
	}
}
