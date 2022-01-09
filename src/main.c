// local includes
#include <warbler/file.h>
#include <warbler/cli.h>
#include <warbler/preprocessor.h>
#include <warbler/tokenizer.h>
#include <warbler/ast/ast.h>
#include <warbler/print.h>

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
	printf("Source:\n%s\n", src);

	Error error = tokenizer_init();
	if (error)
	{
		error("failed to initialize tokenizer");
		free(src);
		return (int)error;
	}

	puts(BAR "TOKENIZER" BAR "\n");

	TokenArray tokens;
	error = tokenize(&tokens, argv[1], src);
	if (error)
	{
		error("failed to tokenize source");
		free(src);
		tokenizer_free();

		return (int)error;
	}

	for (size_t i = 0; i < tokens.length; ++i)
	{
		Token *token = TokenArray_get_ptr(&tokens, i);
		printf("Token\t%d\t:\t", (int)token->type);
		token_println(token);
	}

	puts(BAR "PARSER" BAR "\n");

	AdditiveExpression expr;
	TokenIterator iter = { tokens.buffer };
	
	if ((error = additive_expression_parse(&expr, &iter)) == ERROR_NONE)
	{
		debug("Parsed additive expression :)");
		additive_expression_print_tree(&expr, 1);
	}

	debug("freeing data");
	additive_expression_free(&expr);
	free(src);
	tokenizer_free();
	return error;
}

