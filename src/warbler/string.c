#include <warbler/string.h>

// local includes
#include <warbler/print.h>

// standard library
#include <stdlib.h>
#include <string.h>
#include <assert.h>

String string_default()
{
	return (String) {
		.data = NULL,
		.length = 0
	};
}

String string_from(const char *text)
{
	return (String) {
		.data = text,
		.length = strlen(text)
	};
}

void string_fprint(const String *string, FILE *stream)
{
	assert(stream != NULL);
	assert(string != NULL);
	assert(string->data != NULL);
	assert(string->length > 0);

	fwrite(string->data, sizeof(char), string->length, stream);
}

void string_print(const String * string)
{
	string_fprint(string, stdout);
}


void string_println(const String *string)
{
	string_fprint(string, stdout);
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
		errorm("failed to allocate string buffer for duplication");
		return NULL;
	}

	for (size_t i = 0; i < string->length; ++i)
	{
		out[i] = string->data[i];
	}

	out[string->length] = 0;

	return out;
}
