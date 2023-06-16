#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ir/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ir/ValueType.hpp"

namespace parka::ast
{
	IdentifierExpressionAst *IdentifierExpressionAst::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto *syntax = new IdentifierExpressionAst(*identifier);

		return syntax;
	}

	ir::ExpressionIr *IdentifierExpressionAst::validate(SymbolTable& symbolTable)
	{
		auto *entity = symbolTable.resolve(_identifier);

		if (entity == nullptr)
			return nullptr;

		const auto *valueType = entity->valueType();

		if (!valueType)
			return nullptr;

		auto *context = new ir::IdentifierExpressionIr(*entity, ir::ValueType(*valueType));

		return context;
	}
}
