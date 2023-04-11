#ifndef PARKA_SYNTAX_LITERAL_SYNTAX_HPP
#define PARKA_SYNTAX_LITERAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	struct LiteralSyntax : public ExpressionSyntax
	{
		virtual ~LiteralSyntax() {}

		static Optional<ExpressionSyntaxId> parse(Token& token);
	};
}

#endif
