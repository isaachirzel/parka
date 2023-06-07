#ifndef PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct ExpressionSyntax
	{
		virtual ~ExpressionSyntax() {}

		static Optional<ExpressionSyntaxId> parse(Token& token);
	};
}

#endif
