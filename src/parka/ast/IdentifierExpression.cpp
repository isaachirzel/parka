#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ir/IdentifierExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ir/Type.hpp"

namespace parka::ast
{
	// ir::ExpressionIr *IdentifierExpressionAst::validate(SymbolTable& symbolTable)
	// {
	// 	auto *entity = symbolTable.resolve(_identifier);

	// 	if (entity == nullptr)
	// 		return nullptr;

	// 	const auto *Type = entity->valueType();

	// 	if (!Type)
	// 		return nullptr;

	// 	auto *context = new ir::IdentifierExpressionIr(*entity, ir::Type(*Type));

	// 	return context;
	// }
}
