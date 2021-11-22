#include <warbler/error.h>

// standard library
#include <stdio.h>

const char * const error_prompt_color	= "\033[31merror:\033[0m";
const char * const error_prompt_plain	= "error:";
bool is_color_output = true;

void print_error(const char *msg)
{
	const char *error_prompt = is_color_output
		? error_prompt_color
		: error_prompt_plain;

	printf("%s %s\n", error_prompt, msg);
}
