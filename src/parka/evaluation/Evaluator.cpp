#include "parka/evaluation/Evaluator.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/evaluation/IntrinsicOperator.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/TypeIr.hpp"
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
		auto& returnValue = state.pushReturnValue(ir.prototype().returnType());

		evaluatePrototype(ir.prototype(), arguments, state);
		evaluateBlockStatement(ir.body(), state);

		state.clearFunctionValues();

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

			// case StatementType::Expression:
			// 	return eva

			case StatementType::Return:
				return evaluateReturnStatement(static_cast<const ReturnStatementIr&>(ir), state);

			// case StatementType::Break:
			// 	return 

			// case StatementType::Continue:
			// 	return 

			// case StatementType::Yield:
			// 	return 

			// case StatementType::For:
			// 	return 

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

		log::note("Declaring variable: $", value);
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

	void evaluateBlockStatement(const BlockStatementIr& ir, LocalState& state)
	{
		for (const auto *statement : ir.statements())
		{
			evaluateStatement(*statement, state);

			if (state.isReturning())
				break;
		}
	}

	void evaluateAssignmentStatement(const AssignmentStatementIr& ir, LocalState& state)
	{
		// auto& lhs = state.find(ir.identifier().value());
		// auto& rhs = evaluateExpression(ir.value(), state);

		

		log::notImplemented(here());

		// value.set(
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
