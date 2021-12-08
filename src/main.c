// local includes
#include <warbler/file.h>
#include <warbler/cli.h>
#include <warbler/preprocessor.h>
#include <warbler/tokenizer.h>
#include <warbler/parser.h>

// standard library
#include <stdio.h>
#include <stdlib.h>

#define BAR "\n###########################################################\n"

int main(int argc, char *argv[])
{
	if (!validate_cli_args(argc, argv))
		return 1;

	char *src = read_file(argv[1]);

	if (!src)
		return ERROR_FILE;

	preprocess(src);
	printf("success:\n%s\n", src);

	Error error = tokenizer_init();
	if (error)
	{
		print_error("failed to initialize tokenizer");
		free(src);
		return (int)error;
	}

	puts(BAR "TOKENIZER" BAR "\n");


	HxArray *tokens;
	error = tokenize(&tokens, src);
	if (error)
	{
		print_error("failed to tokenize source");
		free(src);
		tokenizer_free();

		return (int)error;
	}

	puts(BAR "PARSER" BAR "\n");

	const Token *iter = (const Token*)hxarray_front(tokens);
	Identifier *identifier;
	error = parse_identifier(&identifier, &iter);
	if (error)
	{
		printf("failed to parse and got error: %d\n", error);
	}

	fputs("Parsed identifier: ", stdout);
	string_println(identifier->text);

	free(src);
	tokenizer_free();
	return 0;
}

