#include "parka/evaluation/Evaluator.hpp"
#include "parka/evaluation/IntegerValue.hpp"
#include "parka/evaluation/VoidValue.hpp"
#include "parka/ir/Value.hpp"
#include "parka/log/Log.hpp"

using namespace parka::ir;

namespace parka::evaluation
{
	void evaluate(const Ir& ir)
	{
		auto *entryPoint = ir.entryPoint();

		if (!entryPoint)
		{
			// TODO: Get program name?
			log::error("Unable to evaluate this program as there is no entry point. Please implement a function named `main` in the global scope.");
			return;
		}

		evaluateFunction(*entryPoint, {});
	}

	void evaluateFunction(const FunctionIr& ir, const Array<ExpressionIr*>& arguments)
	{
		auto state = StateTable();

		evaluatePrototype(ir.prototype(), arguments, state);
		evaluateExpression(ir.body(), state);
	}

	void evaluatePrototype(const PrototypeIr& ir, const Array<ExpressionIr*>& arguments, StateTable& state)
	{
		assert(ir.parameters().length() == arguments.length());

		for (usize i = 0; i < arguments.length(); ++i)
		{
			const auto& parameter = *ir.parameters()[i];
			const auto& argument = *arguments[i];
			auto& value = evaluateExpression(argument, state);

			state.insert((usize)&parameter, &value);
		}
	}

	void evaluateStatement(const StatementIr& ir, StateTable& state)
	{
		auto& declaration = dynamic_cast<const DeclarationStatementIr&>(ir);

		return evaluateDeclarationStatement(declaration, state);
	}

	void evaluateDeclarationStatement(const DeclarationStatementIr& ir, StateTable& state)
	{
		auto& value = evaluateExpression(ir.value(), state);
		const auto key = (usize)static_cast<const ir::Value*>(&ir.variable());

		state.insert(key, &value);
	}

	Value& evaluateExpression(const ExpressionIr& ir, StateTable& state)
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
				return evaluateIntegerLiteral(static_cast<const IntegerLiteralIr&>(ir));

			case ExpressionType::StringLiteral:
				break;
				
			default:
				break;
		}

		log::fatal("Unable to evaluate Expression with Type: $", ir.expressionType);
	}

	Value& evaluateBinaryExpression(const BinaryExpressionIr& ir, StateTable& state)
	{
		auto& lhs = evaluateExpression(ir.lhs(), state);
		auto& rhs = evaluateExpression(ir.rhs(), state);
		auto& result = lhs.add(rhs);

		return result;
	}

	Value& evaluateBlock(const BlockExpressionIr& ir, StateTable& state)
	{
		for (const auto *statement : ir.statements())
		{
			// TODO: handle returns
			evaluateStatement(*statement, state);
		}

		return *new VoidValue();
	}

	Value& evaluateIdentifierExpression(const IdentifierExpressionIr& ir, StateTable& state)
	{
		const auto key = (usize)&ir.value();
		auto *value = state.get(key);

		return *value;
	}

	Value& evaluateIntegerLiteral(const IntegerLiteralIr& ir)
	{
		return *new IntegerValue(ir.valueType(), ir.value());
	}
}
