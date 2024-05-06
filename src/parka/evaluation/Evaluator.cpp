#include "parka/evaluation/Evaluator.hpp"
#include "parka/evaluation/IntrinsicOperators.hpp"
#include "parka/ir/DeclarationStatement.hpp"
#include "parka/ir/IntrinsicOperator.hpp"
#include "parka/ir/ReturnStatement.hpp"
#include "parka/ir/Type.hpp"
#include "parka/log/Log.hpp"

using namespace parka::ir;

namespace parka::evaluation
{
	void evaluate(const Ir& ir)
	{
		auto state = State();
		auto *entryPoint = ir.entryPoint();

		if (!entryPoint)
		{
			// TODO: Get program name?
			log::fatal("Unable to evaluate this program as there is no entry point. Please implement a function named `main` in the global scope.");
		}

		auto& result = evaluateFunction(*entryPoint, {}, state);

		log::note("Result of $(): $", entryPoint->symbol(), result);
	}

	Value& evaluateFunction(const FunctionIr& ir, const Array<ExpressionIr*>& arguments, State& state)
	{
		auto& returnValue = state.push(ir.prototype().returnType());
		auto frame = state.createFrame();

		evaluatePrototype(ir.prototype(), arguments, state);
		evaluateExpression(ir.body(), state);

		if (state.hasReturnValue())
			returnValue.set(state.returnValue());

		return returnValue;
	}

	void evaluatePrototype(const PrototypeIr& ir, const Array<ExpressionIr*>& arguments, State& state)
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

	void evaluateStatement(const StatementIr& ir, State& state)
	{
		switch (ir.statementType)
		{
			case StatementType::Declaration:
				return evaluateDeclarationStatement(static_cast<const DeclarationStatementIr&>(ir), state);

			case StatementType::Return:
				return evaluateReturnStatement(static_cast<const ReturnStatementIr&>(ir), state);

			default:
				break;
		}

		log::fatal("Unable to evaluate statement of type: $", (int)ir.statementType);
	}

	void evaluateReturnStatement(const ir::ReturnStatementIr& ir, State& state)
	{
		auto& value = ir.hasValue()
			? evaluateExpression(ir.value(), state)
			: state.push(ir::Type::voidType);

		state.returnValue(value);
	}

	void evaluateDeclarationStatement(const DeclarationStatementIr& ir, State& state)
	{
		auto& value = evaluateExpression(ir.value(), state);

		value.setNode(ir.variable());

		log::note("Declaring variable: $", value);
	}

	Value& evaluateOperator(const OperatorIr& op, Value& left, Value& right, State& state)
	{
		if (op.isIntrinsic)
			return evaluateIntrinsicOperator(dynamic_cast<const ir::IntrinsicOperatorIr&>(op), left, right, state);

		log::notImplemented(here());
	}

	Value& evaluateIntrinsicOperator(const IntrinsicOperatorIr& op, Value& left, Value& right, State& state)
	{
		auto index = &op - IntrinsicOperatorIr::entries;
		auto& value = intrinsicOperators[index](left, right, state);

		return value;
	}

	Value& evaluateExpression(const ExpressionIr& ir, State& state)
	{
		switch (ir.expressionType)
		{
			case ExpressionType::Binary:
				return evaluateBinaryExpression(static_cast<const BinaryExpressionIr&>(ir), state);

			case ExpressionType::Block:
				return evaluateBlock(static_cast<const BlockExpressionIr&>(ir), state);

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

	Value& evaluateBinaryExpression(const BinaryExpressionIr& ir, State& state)
	{
		auto& lhs = evaluateExpression(ir.lhs(), state);
		auto& rhs = evaluateExpression(ir.rhs(), state);
		auto& result = evaluateOperator(ir.op(), lhs, rhs, state);

		return result;
	}

	Value& evaluateBlock(const BlockExpressionIr& ir, State& state)
	{
		for (const auto *statement : ir.statements())
		{
			// TODO: handle returns
			evaluateStatement(*statement, state);

			if (state.hasReturnValue())
				break;
		}

		auto& value = state.push(ir::Type::voidType);
		
		return value;
	}

	Value& evaluateIdentifierExpression(const IdentifierExpressionIr& ir, State& state)
	{
		auto& value = state.find(ir.value());

		return value;
	}

	Value& evaluateIntegerLiteral(const IntegerLiteralIr& ir, State& state)
	{
		auto& result = state.push(ir.type(), ir.value());

		return result;		
	}
}
