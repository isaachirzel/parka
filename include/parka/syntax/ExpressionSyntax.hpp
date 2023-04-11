#ifndef PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP

#include "parka/data/ExpressionId.hpp"
#include "parka/Token.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct ExpressionSyntax
	{
		static Optional<ExpressionId> parse(Token& token);

		virtual ~ExpressionSyntax() {}
	};
}

#endif
