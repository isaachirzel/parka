// local includes
#include <warbler/util/file.hpp>
#include <warbler/cli.hpp>
#include <warbler/preprocessor.hpp>
#include <warbler/lexicon/tokenizer.hpp>
#include <warbler/syntax/ast.hpp>
#include <warbler/util/print.hpp>

// standard library
#include <cstdio>
#include <cstdlib>

#define BAR "\n###########################################################\n"

using namespace warbler;

int main()
{
	// if (!validate_cli_args(argc, argv))
	// 	return 1;

	// char *src = read_file(argv[1]);

	// if (!src)
	// 	return ERROR_FILE;

	// preprocess(src);
	// printf("Source:\n%s\n", src);

	// Error error = tokenizer_init();
	// if (error)
	// {
	// 	errorm("failed to initialize tokenizer");
	// 	free(src);
	// 	return (int)error;
	// }

	// puts(BAR "TOKENIZER" BAR "\n");

	// auto res = tokenize(argv[1], src);
	
	// if (!res)
	// {
	// 	errorm("failed to tokenize source");
	// 	free(src);

	// 	return (int)error;
	// }

	// auto tokens = res.unwrap();

	// for (size_t i = 0; i < tokens.size(); ++i)
	// {
	// 	auto& token = tokens[i];
	// 	printf("Token\t%d\t:\t", (int)token.type);
	// 	token_println(&token);
	// }

	// puts(BAR "PARSER" BAR "\n");

	// AdditiveExpression expr;
	// TokenIterator iter = tokens.begin();
	
	// if ((error = additive_expression_parse(&expr, iter)) == ERROR_NONE)
	// {
	// 	debug("Parsed additive expression :)");
	// 	additive_expression_print_tree(&expr, 1);
	// }

	// debug("freeing data");
	// additive_expression_free(&expr);
	// free(src);
	return 0;
}

