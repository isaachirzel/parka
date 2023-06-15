#include "parka/ast/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"


namespace parka
{
	IdentifierExpressionSyntax *IdentifierExpressionSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto *syntax = new IdentifierExpressionSyntax(*identifier);

		return syntax;
	}

	ExpressionContext *IdentifierExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
