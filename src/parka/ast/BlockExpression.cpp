#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ir/BlockExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Statement.hpp"

namespace parka::ast
{
	// ir::ExpressionIr *BlockExpressionAst::validate(SymbolTable& symbolTable)
	// {
	// 	bool success = false;
	// 	auto statements = Array<ir::StatementIr*>(_statements.length());
	// 	const auto& valueType = ir::ValueType::voidType;

	// 	for (auto *syntax : _statements)
	// 	{
	// 		// TODO: Get and update valueType
	// 		auto *context = syntax->validate(symbolTable);

	// 		if (!context)
	// 		{
	// 			success = false;
	// 			continue;
	// 		}

	// 		statements.push(context);
	// 	}

	// 	if (!success)
	// 		return {};

	// 	auto *context = new ir::BlockExpressionIr(std::move(statements), ir::ValueType(valueType));

	// 	return context;
	// }
}
