#include "parka/evaluation/Evaluator.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/JumpType.hpp"
#include "parka/enum/TypeCategory.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/evaluation/IntrinsicBinaryOperator.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/BoolLiteralIr.hpp"
#include "parka/ir/CastExpressionIr.hpp"
#include "parka/ir/ConditionalExpressionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/FloatLiteralIr.hpp"
#include "parka/ir/IfStatementIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/StringLiteralIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"
#include <stdexcept>
#include <type_traits>

using namespace parka::ir;

namespace parka::evaluation
{
	void evaluate(const Ir& ir)
	{
		auto globalState = GlobalState();
		auto state = LocalState(globalState);
		auto *entryPoint = ir.entryPoint();

		if (!entryPoint)
			log::fatal("Unable to evaluate `$` as there is no entry point. Please implement a function named `main` in the global scope.", ir.name());

		auto& result = evaluateFunction(*entryPoint, {}, state);

		log::debug("Result of $(): $", entryPoint->symbol(), result);
	}

	Value& evaluateFunction(const FunctionIr& ir, const Array<ArgumentIr>& arguments, LocalState& state)
	{
		usize previousReturnValueIndex = state.getReturnValueIndex();
		auto& returnValue = state.pushReturnValue(ir.prototype().returnType());
		usize index = state.getScopeIndex();

		evaluatePrototype(ir.prototype(), arguments, state);

		if (!ir.hasBody())
		{
			log::fatal("$() is not implemented.", ir.symbol());
		}
		
		evaluateFunctionBody(ir.body(), state);

		// TODO: This shouldn't do this for exceptions

		state.setReturning(JumpType::None);
		state.clearScopeValues(index);
		state.setReturnValueIndex(previousReturnValueIndex);

		return returnValue;
	}

	void evaluatePrototype(const PrototypeIr& ir, const Array<ArgumentIr>& arguments, LocalState& state)
	{
		for (usize i = 0; i < arguments.length(); ++i)
		{
			auto& parameter = *ir.parameters()[i];
			auto& argument = arguments[i];
			auto& argumentValue = evaluateExpression(argument.value(), state);

			argumentValue.setNode(parameter);
		}
	}

	void evaluateFunctionBody(const ir::FunctionBodyIr& ir, LocalState& state)
	{
		if (ir.isExpression())
		{
			auto& expressionValue = evaluateExpression(ir.expression(), state);

			state.returnValue().setValue(expressionValue);

			return;
		}

		evaluateBlockStatement(ir.blockStatement(), state);
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

			case StatementType::If:
				return evaluateIfStatement(static_cast<const IfStatementIr&>(ir), state);

			default:
				break;
		}

		log::fatal("Unable to evaluate statement of type: $", (int)ir.statementType);
	}

	void evaluateDeclarationStatement(const DeclarationStatementIr& ir, LocalState& state)
	{
		auto& variableValue = evaluateExpression(ir.value(), state);

		variableValue.setNode(ir.variable());

		log::debug("Declaring variable: $", variableValue);
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

			state.returnValue().setValue(value);
		}

		state.setReturning(JumpType::Return);
	}

	void evaluateBreakStatement(const ir::BreakStatementIr&, LocalState& state)
	{
		state.setReturning(JumpType::Break);
	}

	void evaluateContinueStatement(const ir::ContinueStatementIr&, LocalState& state)
	{
		state.startContinue();
	}

	void evaluateYieldStatement(const ir::YieldStatementIr&, LocalState&)
	{
		log::notImplemented(here());
	}

	void evaluateForStatement(const ir::ForStatementIr& ir, LocalState& state)
	{
		usize index = state.getScopeIndex();

		evaluateDeclarationStatement(ir.declaration(), state);

		while (true)
		{
			auto& conditionValue = evaluateExpression(ir.condition(), state);

			if (!conditionValue.getValue<bool>())
				break;

			evaluateBlockStatement(ir.body(), state);

			if (state.isBreaking())
				break;

			evaluateStatement(ir.action(), state);

			state.cancelContinue();
		}

		state.cancelBreak();

		state.clearScopeValues(index);
	}

	void evaluateBlockStatement(const BlockStatementIr& ir, LocalState& state)
	{
		usize index = state.getScopeIndex();

		for (const auto *statement : ir.statements())
		{
			evaluateStatement(*statement, state);

			if (state.isJumping())
				break;
		}

		state.clearScopeValues(index);
	}

	void evaluateAssignmentStatement(const AssignmentStatementIr& ir, LocalState& state)
	{
		auto& lhs = state.findValue(ir.identifier().value());
		auto& rhs = evaluateExpression(ir.value(), state);

		evaluateAssignmentOperator(ir.op(), lhs, rhs, state);
	}
	
	void evaluateIfStatement(const IfStatementIr& ir, LocalState& state)
	{
		auto& conditionValue = evaluateExpression(ir.condition(), state);
		
		if (conditionValue.getValue<bool>())
		{
			evaluateStatement(ir.thenCase(), state);
		}
		else if (ir.hasElseCase())
		{
			evaluateStatement(ir.elseCase(), state);
		}
	}

	Value& evaluateExpression(const ExpressionIr& ir, LocalState& state)
	{
		switch (ir.expressionType)
		{
			case ExpressionType::Binary:
				return evaluateBinaryExpression(static_cast<const BinaryExpressionIr&>(ir), state);

			case ExpressionType::Call:
				return evaluateCallExpression(static_cast<const ir::CallExpressionIr&>(ir), state);

			case ExpressionType::Conditional:
				return evaluateConditionalExpression(static_cast<const ir::ConditionalExpressionIr&>(ir), state);

			case ExpressionType::Identifier:
				return evaluateIdentifierExpression(static_cast<const IdentifierExpressionIr&>(ir), state);

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::Cast:
				return evaluateCastExpression(static_cast<const CastExpressionIr&>(ir), state);

			case ExpressionType::BoolLiteral:
				return evaluateBoolLiteral(static_cast<const BoolLiteralIr&>(ir), state);

			case ExpressionType::CharLiteral:
				return evaluateCharLiteral(static_cast<const CharLiteralIr&>(ir), state);

			case ExpressionType::FloatLiteral:
				return evaluateFloatLiteral(static_cast<const FloatLiteralIr&>(ir), state);

			case ExpressionType::IntegerLiteral:
				return evaluateIntegerLiteral(static_cast<const IntegerLiteralIr&>(ir), state);

			case ExpressionType::StringLiteral:
				return evaluateStringLiteral(static_cast<const StringLiteralIr&>(ir), state);
				
			default:
				break;
		}

		log::fatal("Unable to evaluate Expression with TypeIr: $", ir.expressionType);
	}

	Value& evaluateBinaryExpression(const BinaryExpressionIr& ir, LocalState& state)
	{
		auto& lhs = evaluateExpression(ir.lhs(), state);
		auto& rhs = evaluateExpression(ir.rhs(), state);
		auto& result = evaluateBinaryOperator(ir.op(), lhs, rhs, state);

		return result;
	}

	Value& evaluateCallExpression(const ir::CallExpressionIr& ir, LocalState& state)
	{
		return evaluateFunction(ir.subject(), ir.arguments(), state);
	}

	Value& evaluateConditionalExpression(const ir::ConditionalExpressionIr& ir, LocalState& state)
	{
		auto& conditionValue = evaluateExpression(ir.condition(), state);
		auto& value = conditionValue.getValue<bool>()
			? evaluateExpression(ir.thenCase(), state)
			: evaluateExpression(ir.elseCase(), state);

		return value;
	}

	Value& evaluateIdentifierExpression(const IdentifierExpressionIr& ir, LocalState& state)
	{
		// TODO: This makes no sense for function calls

		auto& value = state.findValue(ir.value());

		return value;
	}

	Value& evaluateCastExpression(const ir::CastExpressionIr& ir, LocalState& state)
	{
		auto& expressionValue = evaluateExpression(ir.expression(), state);
		auto& castedValue = state.pushValue(ir.type());

		evaluateConversion(ir.conversion(), castedValue, expressionValue, state);

		return castedValue;
	}

	Value& evaluateBoolLiteral(const ir::BoolLiteralIr& ir, LocalState& state)
	{
		auto& result = state.pushValue(ir.type());

		result.setValue(ir.value());

		return result;
	}

	Value& evaluateCharLiteral(const ir::CharLiteralIr& ir, LocalState& state)
	{
		auto& result = state.pushValue(ir.type());

		result.setValue(ir.value());

		return result;
	}

	Value& evaluateFloatLiteral(const ir::FloatLiteralIr& ir, LocalState& state)
	{
		auto& result = state.pushValue(ir.type());

		result.setValue(ir.value());

		return result;
	}

	Value& evaluateIntegerLiteral(const IntegerLiteralIr& ir, LocalState& state)
	{
		auto& result = state.pushValue(ir.type());

		result.setValue(ir.value());

		return result;
	}

	Value& evaluateStringLiteral(const ir::StringLiteralIr& ir, LocalState& state)
	{
		auto& result = state.pushValue(ir.type());

		result.setValue(ir.value().c_str());

		return result;
	}

	template <typename Left, typename Right, typename Return>
	Return executeIntegerBinaryOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				return Return(l + (Left)r);

			case BinaryExpressionType::Subtract:
				return Return(l - (Left)r);

			case BinaryExpressionType::Multiply:
				return Return(l * (Left)r);

			case BinaryExpressionType::Divide:
				return Return(l / (Left)r);

			case BinaryExpressionType::Modulus:
				return Return(l % (Left)r);

			case BinaryExpressionType::BitwiseOr:
				return Return(l | (Left)r);

			case BinaryExpressionType::BitwiseXor:
				return Return(l ^ (Left)r);

			case BinaryExpressionType::BitwiseAnd:
				return Return(l & (Left)r);

			case BinaryExpressionType::LeftShift:
				return Return(l << (Left)r);

			case BinaryExpressionType::RightShift:
				return Return(l >> (Left)r);

			case BinaryExpressionType::LessThan:
				return Return(l < (Left)r);

			case BinaryExpressionType::GreaterThan:
				return Return(l > (Left)r);

			case BinaryExpressionType::LessThanOrEqualTo:
				return Return(l <= (Left)r);

			case BinaryExpressionType::GreaterThanOrEqualTo:
				return Return(l >= (Left)r);

			case BinaryExpressionType::Equals:
				return Return(l == (Left)r);

			case BinaryExpressionType::NotEquals:
				return Return(l != (Left)r);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return>
	Return executeFloatBinaryOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				return Return(l + (Left)r);

			case BinaryExpressionType::Subtract:
				return Return(l - (Left)r);

			case BinaryExpressionType::Multiply:
				return Return(l * (Left)r);

			case BinaryExpressionType::Divide:
				return Return(l / (Left)r);

			case BinaryExpressionType::LessThan:
				if constexpr (std::is_same_v<Return, bool>)
					return Return(l < Left(r));
				break;

			case BinaryExpressionType::GreaterThan:
				if constexpr (std::is_same_v<Return, bool>)
					return Return(l > Left(r));
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if constexpr (std::is_same_v<Return, bool>)
					return Return(l <= Left(r));

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if constexpr (std::is_same_v<Return, bool>)
					return Return(l >= Left(r));
				break;

			case BinaryExpressionType::Equals:
				if constexpr (std::is_same_v<Return, bool>)
					return Return(l == Left(r));
				break;

			case BinaryExpressionType::NotEquals:
				if constexpr (std::is_same_v<Return, bool>)
					return Return(l != Left(r));
				break;

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return>
	Return executeCharBinaryOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return Return(l == (Left)r);

			case BinaryExpressionType::NotEquals:
				return Return(l != (Left)r);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return>
	Return executeBoolBinaryOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return Return(l == (Left)r);

			case BinaryExpressionType::NotEquals:
				return Return(l != (Left)r);

			case BinaryExpressionType::BooleanOr:
				return Return(l || r);

			case BinaryExpressionType::BooleanAnd:
				return Return(l && r);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return, Return (*operation) (BinaryExpressionType, Left, Right)>
	Value& evaluateIntrinsicBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		auto returnValue = operation(ir.binaryExpressionType(), left.getValue<Left>(), right.getValue<Right>());
		auto& value = state.pushValue(ir.returnType());

		value.setValue<Return>(returnValue);

		return value;
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicIntegerBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, executeIntegerBinaryOperation>(ir, left, right, state);
	}

	template <typename Left, typename Right>
	Value& evaluateIntrinsicIntegerBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		switch (ir.returnType().typeCategory)
		{
			case TypeCategory::Integer:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, Integer>(ir, left, right, state);

			case TypeCategory::I8:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, i8>(ir, left, right, state);

			case TypeCategory::I16:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, i16>(ir, left, right, state);

			case TypeCategory::I32:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, i32>(ir, left, right, state);

			case TypeCategory::I64:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, i64>(ir, left, right, state);

			case TypeCategory::U8:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, u8>(ir, left, right, state);

			case TypeCategory::U16:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, u16>(ir, left, right, state);

			case TypeCategory::U32:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, u32>(ir, left, right, state);

			case TypeCategory::U64:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Right, u64>(ir, left, right, state);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());
	}

	template <typename Left>
	Value& evaluateIntrinsicIntegerBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		switch (ir.rightType().typeCategory)
		{
			case TypeCategory::Integer:
				return evaluateIntrinsicIntegerBinaryOperator<Left, Integer>(ir, left, right, state);

			case TypeCategory::I8:
				return evaluateIntrinsicIntegerBinaryOperator<Left, i8>(ir, left, right, state);

			case TypeCategory::I16:
				return evaluateIntrinsicIntegerBinaryOperator<Left, i16>(ir, left, right, state);

			case TypeCategory::I32:
				return evaluateIntrinsicIntegerBinaryOperator<Left, i32>(ir, left, right, state);

			case TypeCategory::I64:
				return evaluateIntrinsicIntegerBinaryOperator<Left, i64>(ir, left, right, state);

			case TypeCategory::U8:
				return evaluateIntrinsicIntegerBinaryOperator<Left, u8>(ir, left, right, state);

			case TypeCategory::U16:
				return evaluateIntrinsicIntegerBinaryOperator<Left, u16>(ir, left, right, state);

			case TypeCategory::U32:
				return evaluateIntrinsicIntegerBinaryOperator<Left, u32>(ir, left, right, state);

			case TypeCategory::U64:
				return evaluateIntrinsicIntegerBinaryOperator<Left, u64>(ir, left, right, state);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicFloatBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, executeFloatBinaryOperation>(ir, left, right, state);
	}

	template <typename Left, typename Right>
	Value& evaluateIntrinsicFloatBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		switch (ir.returnType().typeCategory)
		{
			case TypeCategory::Float:
				return evaluateIntrinsicFloatBinaryOperator<Left, Right, Float>(ir, left, right, state);

			case TypeCategory::F32:
				return evaluateIntrinsicFloatBinaryOperator<Left, Right, f32>(ir, left, right, state);

			case TypeCategory::F64:
				return evaluateIntrinsicFloatBinaryOperator<Left, Right, f64>(ir, left, right, state);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());
	}

	template <typename Left>
	Value& evaluateIntrinsicFloatBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		switch (ir.rightType().typeCategory)
		{
			case TypeCategory::Float:
				return evaluateIntrinsicFloatBinaryOperator<Left, Float>(ir, left, right, state);

			case TypeCategory::F32:
				return evaluateIntrinsicFloatBinaryOperator<Left, f32>(ir, left, right, state);

			case TypeCategory::F64:
				return evaluateIntrinsicFloatBinaryOperator<Left, f64>(ir, left, right, state);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicBoolBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, executeBoolBinaryOperation>(ir, left, right, state);
	}

	template <typename Left, typename Right>
	Value& evaluateIntrinsicBoolBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		if (ir.returnType().typeCategory != TypeCategory::Bool)
			log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());

		return evaluateIntrinsicBoolBinaryOperator<Left, Right, bool>(ir, left, right, state);
	}

	template <typename Left>
	Value& evaluateIntrinsicBoolBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		if (ir.rightType().typeCategory != TypeCategory::Bool)
			log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());

		return evaluateIntrinsicBoolBinaryOperator<Left, bool>(ir, left, right, state);
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicCharBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, executeCharBinaryOperation>(ir, left, right, state);
	}

	template <typename Left, typename Right>
	Value& evaluateIntrinsicCharBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		if (ir.returnType().typeCategory != TypeCategory::Char)
			log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());

		return evaluateIntrinsicCharBinaryOperator<Left, Right, char>(ir, left, right, state);
	}

	template <typename Left>
	Value& evaluateIntrinsicCharBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		if (ir.rightType().typeCategory != TypeCategory::Char)
			log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());

		return evaluateIntrinsicCharBinaryOperator<Left, char>(ir, left, right, state);
	}

	Value& evaluateIntrinsicBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		switch (ir.leftType().typeCategory)
		{
			case TypeCategory::Integer:
				return evaluateIntrinsicIntegerBinaryOperator<Integer>(ir, left, right, state);

			case TypeCategory::I8:
				return evaluateIntrinsicIntegerBinaryOperator<i8>(ir, left, right, state);

			case TypeCategory::I16:
				return evaluateIntrinsicIntegerBinaryOperator<i16>(ir, left, right, state);

			case TypeCategory::I32:
				return evaluateIntrinsicIntegerBinaryOperator<i32>(ir, left, right, state);

			case TypeCategory::I64:
				return evaluateIntrinsicIntegerBinaryOperator<i64>(ir, left, right, state);

			case TypeCategory::U8:
				return evaluateIntrinsicIntegerBinaryOperator<u8>(ir, left, right, state);

			case TypeCategory::U16:
				return evaluateIntrinsicIntegerBinaryOperator<u16>(ir, left, right, state);

			case TypeCategory::U32:
				return evaluateIntrinsicIntegerBinaryOperator<u32>(ir, left, right, state);

			case TypeCategory::U64:
				return evaluateIntrinsicIntegerBinaryOperator<u64>(ir, left, right, state);

			case TypeCategory::Float:
				return evaluateIntrinsicFloatBinaryOperator<Float>(ir, left, right, state);

			case TypeCategory::F32:
				return evaluateIntrinsicFloatBinaryOperator<f32>(ir, left, right, state);

			case TypeCategory::F64:
				return evaluateIntrinsicFloatBinaryOperator<f64>(ir, left, right, state);

			case TypeCategory::Bool:
				return evaluateIntrinsicBoolBinaryOperator<bool>(ir, left, right, state);

			case TypeCategory::Char:
				return evaluateIntrinsicCharBinaryOperator<char>(ir, left, right, state);

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());
	}

	Value& evaluateBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator(ir, left, right, state);
	}

	void evaluateAssignmentOperator(const ir::AssignmentOperatorIr& ir, Value& left, const Value& right, LocalState& state)
	{
		auto op = state.getAssignmentOperator(ir.left(), ir.right(), ir.assignmentType());

		op(left, right);
	}

	template <typename To, typename From>
	Value& evaluateIntrinsicConversion(Value& to, Value& from)
	{
		auto result = (To)from.getValue<From>();

		to.setValue<To>(result);

		return to;
	}

	template <typename To>
	Value& evaluateIntrinsicIntegerConversion(Value& to, Value& from)
	{
		if (from.type().typeCategory != TypeCategory::Integer)
			log::fatal("Unable to evaluate conversion `($)$`.", to.type(), from.type());

		return evaluateIntrinsicConversion<To, Integer>(to, from);
	}

	template <typename To>
	Value& evaluateIntrinsicFloatConversion(Value& to, Value& from)
	{
		if (from.type().typeCategory != TypeCategory::Float)
			log::fatal("Unable to evaluate conversion `($)$`.", to.type(), from.type());

		return evaluateIntrinsicConversion<To, Float>(to, from);
	}

	Value& evaluateIntrinsicConversion(Value& to, Value& from)
	{
		switch (to.type().typeCategory)
		{
			case TypeCategory::I8:
				return evaluateIntrinsicIntegerConversion<i8>(to, from);
				
			case TypeCategory::I16:
				return evaluateIntrinsicIntegerConversion<i16>(to, from);

			case TypeCategory::I32:
				return evaluateIntrinsicIntegerConversion<i32>(to, from);

			case TypeCategory::I64:
				return evaluateIntrinsicIntegerConversion<i64>(to, from);

			case TypeCategory::U8:
				return evaluateIntrinsicIntegerConversion<u8>(to, from);

			case TypeCategory::U16:
				return evaluateIntrinsicIntegerConversion<u16>(to, from);

			case TypeCategory::U32:
				return evaluateIntrinsicIntegerConversion<u32>(to, from);

			case TypeCategory::U64:
				return evaluateIntrinsicIntegerConversion<u64>(to, from);

			case TypeCategory::F32:
				return evaluateIntrinsicFloatConversion<f32>(to, from);

			case TypeCategory::F64:
				return evaluateIntrinsicFloatConversion<f64>(to, from);

			default:
				break;
		}
		
		log::fatal("Unable to evaluate conversion `($)$`.", to.type(), from.type());
	}

	Value& evaluateConversion(const ir::ConversionIr&, Value& to, Value& from, LocalState&)
	{
		return evaluateIntrinsicConversion(to, from);
	}
}
