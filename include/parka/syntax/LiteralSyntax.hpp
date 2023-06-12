#ifndef PARKA_SYNTAX_LITERAL_SYNTAX_HPP
#define PARKA_SYNTAX_LITERAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka::LiteralSyntax
{
	ExpressionSyntax *parse(Token& token);
}

#endif
