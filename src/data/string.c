// header
#include <grackle/data/string.h>

// standard library
#include <string.h>
#include <stdlib.h>


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

/**
 * @brief allocates copy of string as nul-terminated char array on heap.
 * The memory allocated by this function must bee freed
 * 
 * @param	str	pointer to string struct
 */

char *string_duplicate(string_t *str)
{
	char *buf = malloc(str->len + 1);
	if (!buf) return NULL;
	buf[str->len] = 0;
	strncpy(buf, str->ptr, str->len);
	return buf;
}
