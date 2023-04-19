#ifndef PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct ExpressionSyntax
	{
		static Optional<ExpressionSyntaxId> parse(Token& token);

		virtual ~ExpressionSyntax() {}
	};
}

#endif
