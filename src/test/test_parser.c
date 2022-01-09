#include <warbler/tokenizer.h>

// local headers
#include <warbler/ast/ast.h>
#include <warbler/print.h>

// standard headers
#include <stdio.h>
#include <assert.h>

//const char *src = "foo(3, 4) * 1 / 5 + 2 / hello % 3\n + 3 == 4 >= &hello";
const char *src = "b = a or b and c << 1.7 * 3";

int main()
{
	try(tokenizer_init());

	Error error;

	TokenArray tokens;

	error = tokenize(&tokens, "<in-memory-file>", src);

	if (!error)
	{
		for (size_t i = 0; i < tokens.length; ++i)
			debugf("Token[%zu]: %d", i, tokens.buffer[i].type);

		putchar('\n');

		TokenIterator iter = { tokens.buffer };

		Expression expr;
		error = expression_parse(&expr, &iter);

		if (!error)
		{
			expression_print_tree(&expr, 1);
		}

		expression_free(&expr);

		if (iter.token->type != TOKEN_END_OF_FILE)
		{
			errorf("current token is not EOF: %t", iter.token);
		}
	}

	tokenizer_free();

	return 0;
}