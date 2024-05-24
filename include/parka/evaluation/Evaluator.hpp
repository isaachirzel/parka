#ifndef PARKA_EVALUATION_EVALUATOR_HPP
#define PARKA_EVALUATION_EVALUATOR_HPP

#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/ArgumentIr.hpp"
#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/BoolLiteralIr.hpp"
#include "parka/ir/BreakStatementIr.hpp"
#include "parka/ir/CallExpressionIr.hpp"
#include "parka/ir/CastExpressionIr.hpp"
#include "parka/ir/CharLiteralIr.hpp"
#include "parka/ir/ContinueStatementIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/FloatLiteralIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/IfStatementIr.hpp"
#include "parka/ir/IntegerLiteralIr.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/StringLiteralIr.hpp"
#include "parka/ir/YieldStatementIr.hpp"

namespace parka::evaluation
{
	void evaluate(const ir::Ir& ir);
	Value& evaluateFunction(const ir::FunctionIr& ir, const Array<ir::ArgumentIr>& arguments, LocalState& state);
	void evaluatePrototype(const ir::PrototypeIr& ir, const Array<ir::ArgumentIr>& arguments, LocalState& state);
	void evaluateFunctionBody(const ir::FunctionBodyIr& ir, LocalState& state);
	void evaluateStatement(const ir::StatementIr& ir, LocalState& state);
	void evaluateDeclarationStatement(const ir::DeclarationStatementIr& ir, LocalState& state);
	void evaluateExpressionStatement(const ir::ExpressionStatementIr& ir, LocalState& state);
	void evaluateReturnStatement(const ir::ReturnStatementIr& ir, LocalState& state);
	void evaluateBreakStatement(const ir::BreakStatementIr& ir, LocalState& state);
	void evaluateContinueStatement(const ir::ContinueStatementIr& ir, LocalState& state);
	void evaluateYieldStatement(const ir::YieldStatementIr& ir, LocalState& state);
	void evaluateForStatement(const ir::ForStatementIr& ir, LocalState& state);
	void evaluateBlockStatement(const ir::BlockStatementIr& ir, LocalState& state);
	void evaluateAssignmentStatement(const ir::AssignmentStatementIr& ir, LocalState& state);
	void evaluateIfStatement(const ir::IfStatementIr& ir, LocalState& state);

	Value& evaluateExpression(const ir::ExpressionIr& ir, LocalState& state);
	Value& evaluateBinaryExpression(const ir::BinaryExpressionIr& ir, LocalState& state);
	Value& evaluateCallExpression(const ir::CallExpressionIr& ir, LocalState& state);
	Value& evaluateIdentifierExpression(const ir::IdentifierExpressionIr& ir, LocalState& state);
	Value& evaluateCastExpression(const ir::CastExpressionIr& ir, LocalState& state);
	Value& evaluateBoolLiteral(const ir::BoolLiteralIr& ir, LocalState& state);
	Value& evaluateCharLiteral(const ir::CharLiteralIr& ir, LocalState& state);
	Value& evaluateFloatLiteral(const ir::FloatLiteralIr& ir, LocalState& state);
	Value& evaluateIntegerLiteral(const ir::IntegerLiteralIr& ir, LocalState& state);
	Value& evaluateStringLiteral(const ir::StringLiteralIr& ir, LocalState& state);

	Value& evaluateBinaryOperator(const ir::BinaryOperatorIr& op, Value& left, Value& right, LocalState& state);
	Value& evaluateAssignmentOperator(const ir::AssignmentOperatorIr& op, Value& left, Value& right, LocalState& state);
	Value& evaluateConversion(const ir::ConversionIr& conversion, Value& to, Value& from, LocalState& state);
}

#endif
