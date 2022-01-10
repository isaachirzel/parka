#include <warbler/tokenizer.hpp>

// local headers
#include <warbler/ast/ast.hpp>
#include <warbler/print.hpp>

// standard headers
#include <stdio.h>
#include <assert.h>

//const char *src = "foo(3, 4) * 1 / 5 + 2 / hello % 3\n + 3 == 4 >= &hello";
const char *src = "b = a || b && c << 1.7 * 3";

using namespace warbler;

int main()
{
	try(tokenizer_init());


	auto res = tokenize("<in-memory-file>", src);

	if (res.has_error())
		return res.error();

	std::vector<Token> tokens = res.unwrap();

	for (size_t i = 0; i < tokens.size(); ++i)
		debugf("Token[%zu]: %d", i, tokens[i].type);

	putchar('\n');

	TokenIterator iter = tokens.begin();

	Expression expr;
	auto error = expression_parse(&expr, iter);

	if (!error)
	{
		expression_print_tree(&expr, 1);
	}

	expression_free(&expr);

	if (iter->type != TOKEN_END_OF_FILE)
	{
		errorf("current token is not EOF: %t", *iter);
	}

	return 0;
}