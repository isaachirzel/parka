#include <warbler/file.h>
#include <warbler/preprocessor.h>
#include <warbler/parser.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>

#define BAR "\n###########################################################\n"

int main(void)
{
	// if (!validateCliArgs(argc, argv))
	// 	return 1;

	// char *src = fileRead(argv[1]);

	// if (!src)
	// 	return ERROR_FILE;

	// preprocess(src);
	// printf("Source:\n%s\n", src);

	// Error error = tokenizerInit();
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

	// for (sizeT i = 0; i < tokens.size(); ++i)
	// {
	// 	auto *token = tokens[i];
	// 	printf("Token\t%d\t:\t", (int)token.type);
	// 	tokenPrintln(&token);
	// }

	// puts(BAR "PARSER" BAR "\n");

	// AdditiveExpression expr;
	// TokenIterator iter = tokens.begin();
	
	// if ((error = additiveExpressionParse(&expr, iter)) == ERROR_NONE)
	// {
	// 	debug("Parsed additive expression :)");
	// 	additiveExpressionPrintTree(&expr, 1);
	// }

	// debug("freeing data");
	// additiveExpressionFree(&expr);
	// free(src);
	return 0;
}

