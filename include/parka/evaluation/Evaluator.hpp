#ifndef PARKA_EVALUATION_EVALUATOR_HPP
#define PARKA_EVALUATION_EVALUATOR_HPP

#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/BreakStatementIr.hpp"
#include "parka/ir/ContinueStatementIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/IntegerLiteralIr.hpp"
#include "parka/ir/IntrinsicConversionIr.hpp"
#include "parka/ir/IntrinsicBinaryOperatorIr.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/YieldStatementIr.hpp"

namespace parka::evaluation
{
	void evaluate(const ir::Ir& ir);
	Value& evaluateFunction(const ir::FunctionIr& ir, const Array<ir::ExpressionIr*>& arguments, LocalState& state);
	void evaluatePrototype(const ir::PrototypeIr& ir, const Array<ir::ExpressionIr*>& arguments, LocalState& state);
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
	Value& evaluateExpression(const ir::ExpressionIr& ir, LocalState& state);
	Value& evaluateBinaryExpression(const ir::BinaryExpressionIr& ir, LocalState& state);
	Value& evaluateIdentifierExpression(const ir::IdentifierExpressionIr& ir, LocalState& state);
	Value& evaluateIntegerLiteral(const ir::IntegerLiteralIr& ir, LocalState& state);
	Value& evaluateOperator(const ir::BinaryOperatorIr& op, Value& left, Value& right, LocalState& state);
	Value& evaluateIntrinsicOperator(const ir::IntrinsicBinaryOperatorIr& op, Value& left, Value& right, LocalState& state);
	Value& evaluateConversion(const ir::ConversionIr& conversion, Value& to, Value& from);
	Value& evaluateIntrinsicConversion(const ir::IntrinsicConversionIr& conversion, Value& to, Value& from);
}

#endif
