#include "parka/ast/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	IdentifierExpressionContext::IdentifierExpressionContext(EntityContext& entity) :
	_entity(entity)
	{}

	IdentifierExpressionSyntax *IdentifierExpressionSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto *syntax = new IdentifierExpressionSyntax(*identifier);

		return syntax;
	}

	ExpressionContext *IdentifierExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		auto *entity = symbolTable.resolve(_identifier);

		if (entity == nullptr)
			return nullptr;

		auto *context = new IdentifierExpressionContext(*entity);

		return context;
	}

	const ValueType& IdentifierExpressionContext::valueType() const
	{
		log::notImplemented(here());
	}
}
