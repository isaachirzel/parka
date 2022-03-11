#ifndef WARBLER_SYNTAX_EXPRESSION_PRIMARY_EXPRESSION
#define WARBLER_SYNTAX_EXPRESSION_PRIMARY_EXPRESSION

#include <warbler/lexicon/token.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>
#include <warbler/syntax/expression/expression.hpp>

namespace warbler::syntax
{
	struct PrimaryExpression
	{
		static Result<Expression> parse(lexicon::Token& token);
	};
}

#endif
