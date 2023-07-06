#ifndef PARKA_EVALUATION_EVALUATOR_HPP
#define PARKA_EVALUATION_EVALUATOR_HPP

#include "parka/evaluation/Value.hpp"
#include "parka/ir/BinaryExpression.hpp"
#include "parka/ir/BlockExpression.hpp"
#include "parka/ir/DeclarationStatement.hpp"
#include "parka/ir/IdentifierExpression.hpp"
#include "parka/ir/IntegerLiteral.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/util/Table.hpp"

namespace parka::evaluation
{
	using StateTable = Table<usize, Value*>;

	void evaluate(const ir::Ir& ir);
	void evaluateFunction(const ir::FunctionIr& ir, const Array<ir::ExpressionIr*>& arguments);
	void evaluatePrototype(const ir::PrototypeIr& ir, const Array<ir::ExpressionIr*>& arguments, StateTable& state);
	void evaluateStatement(const ir::StatementIr& ir, StateTable& state);
	void evaluateDeclarationStatement(const ir::DeclarationStatementIr& ir, StateTable& state);
	Value& evaluateExpression(const ir::ExpressionIr& ir, StateTable& state);
	Value& evaluateBinaryExpression(const ir::BinaryExpressionIr& ir, StateTable& state);
	Value& evaluateBlock(const ir::BlockExpressionIr& ir, StateTable& state);
	Value& evaluateIdentifierExpression(const ir::IdentifierExpressionIr& ir, StateTable& state);
	Value& evaluateIntegerLiteral(const ir::IntegerLiteralIr& ir);
}

#endif
