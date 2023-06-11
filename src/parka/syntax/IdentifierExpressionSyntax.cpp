#include "parka/syntax/IdentifierExpressionSyntax.hpp"


namespace parka
{
	IdentifierExpressionSyntax *IdentifierExpressionSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto *syntax = new IdentifierExpressionSyntax(*identifier);

		return syntax;
	}
}
