#ifndef PARKA_EVALUATION_EVALUATOR_HPP
#define PARKA_EVALUATION_EVALUATOR_HPP

#include "parka/evaluation/State.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/IntegerLiteralIr.hpp"
#include "parka/ir/IntrinsicOperatorIr.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/ReturnStatementIr.hpp"

namespace parka::evaluation
{
	void evaluate(const ir::Ir& ir);
	Value& evaluateFunction(const ir::FunctionIr& ir, const Array<ir::ExpressionIr*>& arguments, State& state);
	void evaluatePrototype(const ir::PrototypeIr& ir, const Array<ir::ExpressionIr*>& arguments, State& state);
	void evaluateStatement(const ir::StatementIr& ir, State& state);
	void evaluateDeclarationStatement(const ir::DeclarationStatementIr& ir, State& state);
	void evaluateReturnStatement(const ir::ReturnStatementIr& ir, State& state);
	void evaluateBlockStatement(const ir::BlockStatementIr& ir, State& state);
	void evaluateAssignmentStatement(const ir::AssignmentStatementIr& ir, State& state);
	Value& evaluateExpression(const ir::ExpressionIr& ir, State& state);
	Value& evaluateBinaryExpression(const ir::BinaryExpressionIr& ir, State& state);
	Value& evaluateBlock(const ir::BlockStatementIr& ir, State& state);
	Value& evaluateIdentifierExpression(const ir::IdentifierExpressionIr& ir, State& state);
	Value& evaluateIntegerLiteral(const ir::IntegerLiteralIr& ir, State& state);
	Value& evaluateOperator(const ir::OperatorIr& op, Value& left, Value& right, State& state);
	Value& evaluateIntrinsicOperator(const ir::IntrinsicOperatorIr& op, Value& left, Value& right, State& state);
}

#endif
