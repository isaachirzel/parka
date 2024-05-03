#ifndef PARKA_EVALUATION_EVALUATOR_HPP
#define PARKA_EVALUATION_EVALUATOR_HPP

#include "parka/evaluation/State.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/BinaryExpression.hpp"
#include "parka/ir/BlockExpression.hpp"
#include "parka/ir/DeclarationStatement.hpp"
#include "parka/ir/IdentifierExpression.hpp"
#include "parka/ir/IntegerLiteral.hpp"
#include "parka/ir/Ir.hpp"

namespace parka::evaluation
{
	void evaluate(const ir::Ir& ir);
	Value& evaluateFunction(const ir::FunctionIr& ir, const Array<ir::ExpressionIr*>& arguments, State& state);
	void evaluatePrototype(const ir::PrototypeIr& ir, const Array<ir::ExpressionIr*>& arguments, State& state);
	void evaluateStatement(const ir::StatementIr& ir, State& state);
	void evaluateDeclarationStatement(const ir::DeclarationStatementIr& ir, State& state);
	Value& evaluateExpression(const ir::ExpressionIr& ir, State& state);
	Value& evaluateBinaryExpression(const ir::BinaryExpressionIr& ir, State& state);
	Value& evaluateBlock(const ir::BlockExpressionIr& ir, State& state);
	Value& evaluateIdentifierExpression(const ir::IdentifierExpressionIr& ir, State& state);
	Value& evaluateIntegerLiteral(const ir::IntegerLiteralIr& ir, State& state);
}

#endif
