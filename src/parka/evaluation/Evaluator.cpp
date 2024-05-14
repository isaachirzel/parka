#include "parka/evaluation/Evaluator.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/evaluation/IntrinsicOperator.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/log/Log.hpp"

using namespace parka::ir;

namespace parka::evaluation
{
	void evaluate(const Ir& ir)
	{
		auto state = LocalState();
		auto *entryPoint = ir.entryPoint();

		if (!entryPoint)
			log::fatal("Unable to evaluate `$` as there is no entry point. Please implement a function named `main` in the global scope.", ir.name());

		auto& result = evaluateFunction(*entryPoint, {}, state);

		log::debug("Result of $(): $", entryPoint->symbol(), result);
	}

	Value& evaluateFunction(const FunctionIr& ir, const Array<ExpressionIr*>& arguments, LocalState& state)
	{
		usize previousReturnValueIndex = state.getReturnValueIndex();
		auto& returnValue = state.pushReturnValue(ir.prototype().returnType());
		usize index = state.getScopeIndex();

		evaluatePrototype(ir.prototype(), arguments, state);
		evaluateBlockStatement(ir.body(), state);

		auto& returnValue2 = state.returnValue();

		state.clearScopeValues(index);
		state.setReturnValueIndex(previousReturnValueIndex);

		return returnValue;
	}

	void evaluatePrototype(const PrototypeIr& ir, const Array<ExpressionIr*>& arguments, LocalState& state)
	{
		assert(ir.parameters().length() == arguments.length());

		for (usize i = 0; i < arguments.length(); ++i)
		{
			auto& parameter = *ir.parameters()[i];
			auto& argument = *arguments[i];
			auto& value = evaluateExpression(argument, state);

			value.setNode(parameter);
		}
	}

	void evaluateStatement(const StatementIr& ir, LocalState& state)
	{
		switch (ir.statementType)
		{
			case StatementType::Declaration:
				return evaluateDeclarationStatement(static_cast<const DeclarationStatementIr&>(ir), state);

			case StatementType::Expression:
				return evaluateExpressionStatement(static_cast<const ExpressionStatementIr&>(ir), state);

			case StatementType::Return:
				return evaluateReturnStatement(static_cast<const ReturnStatementIr&>(ir), state);

			case StatementType::Break:
				return evaluateBreakStatement(static_cast<const BreakStatementIr&>(ir), state);

			case StatementType::Continue:
				return evaluateContinueStatement(static_cast<const ContinueStatementIr&>(ir), state);

			case StatementType::Yield:
				return evaluateYieldStatement(static_cast<const YieldStatementIr&>(ir), state);

			case StatementType::For:
				return evaluateForStatement(static_cast<const ForStatementIr&>(ir), state);

			case StatementType::Block:
				return evaluateBlockStatement(static_cast<const BlockStatementIr&>(ir), state);

			case StatementType::Assignment:
				return evaluateAssignmentStatement(static_cast<const AssignmentStatementIr&>(ir), state);

			default:
				break;
		}

		log::fatal("Unable to evaluate statement of type: $", (int)ir.statementType);
	}

	void evaluateDeclarationStatement(const DeclarationStatementIr& ir, LocalState& state)
	{
		auto& value = evaluateExpression(ir.value(), state);

		value.setNode(ir.variable());

		log::debug("Declaring variable: $", value);
	}

	void evaluateExpressionStatement(const ir::ExpressionStatementIr& ir, LocalState& state)
	{
		evaluateExpression(ir.expression(), state);
	}

	void evaluateReturnStatement(const ReturnStatementIr& ir, LocalState& state)
	{
		if (ir.hasValue())
		{
			auto& value = evaluateExpression(ir.value(), state);

			evaluateConversion(ir.conversion(), state.returnValue(), value);
		}

		state.setReturning(ReturningType::Return);
	}

	void evaluateBreakStatement(const ir::BreakStatementIr& ir, LocalState& state)
	{
		log::notImplemented(here());
	}

	void evaluateContinueStatement(const ir::ContinueStatementIr& ir, LocalState& state)
	{
		log::notImplemented(here());
	}

	void evaluateYieldStatement(const ir::YieldStatementIr& ir, LocalState& state)
	{
		log::notImplemented(here());
	}

	void evaluateForStatement(const ir::ForStatementIr& ir, LocalState& state)
	{
		usize index = state.getScopeIndex();

		evaluateDeclarationStatement(ir.declaration(), state);

		auto& conditionValue = state.pushValue(Type::boolType);

		while (true)
		{
			auto& value = evaluateExpression(ir.condition(), state);

			evaluateConversion(ir.conversion(), conditionValue, value);

			if (!conditionValue.getValue<bool>())
				break;

			evaluateBlockStatement(ir.body(), state);
			evaluateStatement(ir.action(), state);
		}

		state.clearScopeValues(index);
	}

	void evaluateBlockStatement(const BlockStatementIr& ir, LocalState& state)
	{
		usize index = state.getScopeIndex();

		for (const auto *statement : ir.statements())
		{
			evaluateStatement(*statement, state);

			if (state.isReturning())
				break;
		}

		state.clearScopeValues(index);
	}

	void evaluateAssignmentStatement(const AssignmentStatementIr& ir, LocalState& state)
	{
		auto& lhs = state.findValue(ir.identifier().value());
		auto& rhs = evaluateExpression(ir.value(), state);

		evaluateConversion(ir.conversion(), lhs, rhs);
	}

	Value& evaluateExpression(const ExpressionIr& ir, LocalState& state)
	{
		switch (ir.expressionType)
		{
			case ExpressionType::Binary:
				return evaluateBinaryExpression(static_cast<const BinaryExpressionIr&>(ir), state);

			case ExpressionType::Call:
				break;

			case ExpressionType::Conditional:
				break;

			case ExpressionType::Identifier:
				return evaluateIdentifierExpression(static_cast<const IdentifierExpressionIr&>(ir), state);

			case ExpressionType::If:
				break;

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::BoolLiteral:
				break;

			case ExpressionType::CharLiteral:
				break;

			case ExpressionType::FloatLiteral:
				break;

			case ExpressionType::IntegerLiteral:
				return evaluateIntegerLiteral(static_cast<const IntegerLiteralIr&>(ir), state);

			case ExpressionType::StringLiteral:
				break;
				
			default:
				break;
		}

		log::fatal("Unable to evaluate Expression with Type: $", ir.expressionType);
	}

	Value& evaluateBinaryExpression(const BinaryExpressionIr& ir, LocalState& state)
	{
		auto& lhs = evaluateExpression(ir.lhs(), state);
		auto& rhs = evaluateExpression(ir.rhs(), state);
		auto& result = evaluateOperator(ir.op(), lhs, rhs, state);

		return result;
	}

	Value& evaluateIdentifierExpression(const IdentifierExpressionIr& ir, LocalState& state)
	{
		auto& value = state.findValue(ir.value());

		return value;
	}

	Value& evaluateIntegerLiteral(const IntegerLiteralIr& ir, LocalState& state)
	{
		auto& result = state.pushValue(ir.type());

		result.setValue(ir.value());

		return result;
	}

	Value& evaluateOperator(const OperatorIr& op, Value& left, Value& right, LocalState& state)
	{
		if (op.isIntrinsic)
			return evaluateIntrinsicOperator(dynamic_cast<const IntrinsicOperatorIr&>(op), left, right, state);

		log::notImplemented(here());
	}

	Value& evaluateIntrinsicOperator(const IntrinsicOperatorIr& opIr, Value& left, Value& right, LocalState& state)
	{
		auto index = (usize)(&opIr - IntrinsicOperatorIr::entries);
		
		assert(index < intrinsicOperatorCount);

		auto& op = intrinsicOperators[index];
		auto& value = op(left, right, state);

		return value;
	}

	Value& evaluateConversion(const ir::ConversionIr& conversion, Value& to, Value& from)
	{
		if (conversion.isIntrinsic())
			return evaluateIntrinsicConversion(static_cast<const ir::IntrinsicConversionIr&>(conversion), to, from);

		log::notImplemented(here());
	}

	Value& evaluateIntrinsicConversion(const ir::IntrinsicConversionIr& conversionIr, Value& to, Value& from)
	{
		auto index = (usize)(&conversionIr - IntrinsicConversionIr::entries);

		assert(index < intrinsicOperatorCount);

		auto& conversion = intrinsicConversions[index];
		auto& value = conversion(to, from);

		return value;
	}
}
