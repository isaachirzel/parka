#include <warbler/data/string.h>

// local includes
#include <warbler/error.h>

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

String string_default()
{
	return (String) {
		.data = NULL,
		.length = 0
	};
}

void string_print(const String * string)
{
	assert(string != NULL);
	assert(string->data != NULL);
	assert(string->length > 0);

	fwrite(string->data, sizeof(char), string->length, stdout);	
}

void string_println(const String *string)
{
	string_print(string);
	putchar('\n');
}

char *string_duplicate(const String *string)
{
	assert(string != NULL);
	assert(string->data != NULL);
	assert(string->length > 0);

	char *out = malloc((string->length + 1) * sizeof(*string->data));

	if (!out)
	{
		print_errorf("%s: failed to allocate string buffer", __func__);
		return NULL;
	}

	for (size_t i = 0; i < string->length; ++i)
	{
		out[i] = string->data[i];
	}

	out[string->length] = 0;

	return out;
}
