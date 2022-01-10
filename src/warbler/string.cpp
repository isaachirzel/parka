#include <warbler/string.hpp>

// local includes
#include <warbler/print.hpp>

// standard library
#include <cstdlib>
#include <cstring>
#include <cassert>

namespace warbler
{
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

		char *out = new char[string->length + 1];

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
}
