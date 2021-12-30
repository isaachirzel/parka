// local includes
#include <warbler/file.h>
#include <warbler/cli.h>
#include <warbler/preprocessor.h>
#include <warbler/tokenizer.h>
#include <warbler/ast/ast.h>

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

	for (size_t i = 0; i < hxarray_length(tokens); ++i)
	{
		Token *token = (Token*)hxarray_at(tokens, i);
		printf("Token\t%d\t:\t", (int)token->type);
		token_println(token);
	}

	puts(BAR "PARSER" BAR "\n");

	AdditiveExpression expr;
	TokenIterator iter = { hxarray_front(tokens) };
	additive_expression_parse(&expr, &iter);
	additive_expression_print_tree(&expr, 1);
	additive_expression_free(&expr);

	// Ast ast;
	// ast_parse(&ast, tokens);

	free(src);
	tokenizer_free();
	return 0;
}

