#include "parka/ast/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/type/ValueType.hpp"

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
		auto *entity = symbolTable.resolve(_identifier);

		if (entity == nullptr)
			return nullptr;

		const auto *valueType = entity->valueType();

		if (!valueType)
			return nullptr;

		auto *context = new IdentifierExpressionContext(*entity, ValueType(*valueType));

		return context;
	}
}
