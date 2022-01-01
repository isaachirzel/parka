#include <warbler/tokenizer.h>

#include <stdio.h>
#include <assert.h>
#include <warbler/ast/ast.h>

const char *src = "foo(3, 4) * 1 / 5 + 2 / hello % 3\n +3 == 4";

int main()
{
	try(tokenizer_init());

	Error error;

	HxArray *tokens;

	error = tokenize(&tokens, "in-memory", src);

	if (!error)
	{
		TokenIterator iter = { hxarray_front(tokens) };

		AdditiveExpression expr;
		error = additive_expression_parse(&expr, &iter);

		if (!error)
		{
			additive_expression_print_tree(&expr, 1);
		}

		additive_expression_free(&expr);
	}

	tokenizer_free();

	return 0;
}