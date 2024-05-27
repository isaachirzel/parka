#include "parka/evaluation/BinaryOperatorEvaluator.hpp"
#include "parka/enum/TypeCategory.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

using namespace parka::ir;

namespace parka::evaluation
{
	template <typename Left, typename Right, typename Return, Return (*operation) (BinaryExpressionType, Left, Right)>
	Value& evaluateIntrinsicBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		auto returnValue = operation(ir.binaryExpressionType(), left.getValue<Left>(), right.getValue<Right>());
		auto& value = state.pushValue(ir.returnType());

		value.setValue<Return>(returnValue);

		return value;
	}

	template <typename Left, typename Right>
	bool _comparisonOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::LessThan:
				return bool(l < (Left)r);

			case BinaryExpressionType::GreaterThan:
				return bool(l > (Left)r);

			case BinaryExpressionType::LessThanOrEqualTo:
				return bool(l <= (Left)r);

			case BinaryExpressionType::GreaterThanOrEqualTo:
				return bool(l >= (Left)r);

			case BinaryExpressionType::Equals:
				return bool(l == (Left)r);

			case BinaryExpressionType::NotEquals:
				return bool(l != (Left)r);

			default:
				break;
		}

		log::fatal("Comparison operation `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right>
	Value& evaluateIntrinsicComparsionBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, bool, _comparisonOperation>(ir, left, right, state);
	}

	template <typename Left, typename Right, typename Return>
	Return _integerOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
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

			default:
				break;
		}

		log::fatal("Integer operation `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicIntegerBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, _integerOperation>(ir, left, right, state);
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

			case parka::TypeCategory::Bool:
				return evaluateIntrinsicComparsionBinaryOperator<Left, Right>(ir, left, right, state);

			default:
				break;
		}

		log::fatal("Integer binary operator `$ $ $` with return type `$` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type(), ir.returnType());
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
	Return _floatOperation(BinaryExpressionType binaryExpressionType, Left l, Right r)
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

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicFloatBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, _floatOperation>(ir, left, right, state);
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

			case parka::TypeCategory::Bool:
				return evaluateIntrinsicComparsionBinaryOperator<Left, Right>(ir, left, right, state);

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

	bool _boolOperation(BinaryExpressionType binaryExpressionType, bool l, bool r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return l == r;

			case BinaryExpressionType::NotEquals:
				return l != r;

			case BinaryExpressionType::BooleanOr:
				return l || r;

			case BinaryExpressionType::BooleanAnd:
				return l && r;

			default:
				break;
		}

		log::fatal("Bool operation `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right, typename Return>
	Value& evaluateIntrinsicBoolBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		return evaluateIntrinsicBinaryOperator<Left, Right, Return, _boolOperation>(ir, left, right, state);
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

	bool _charOperation(BinaryExpressionType binaryExpressionType, char l, char r)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return l == r;

			case BinaryExpressionType::NotEquals:
				return l != r;

			default:
				break;
		}

		log::fatal("Binary operator `$ $ $` cannot be evaluated.", l, binaryExpressionType, r);
	}

	template <typename Left, typename Right>
	Value& evaluateIntrinsicCharBinaryOperator(const BinaryOperatorIr& ir, Value& left, Value& right, LocalState& state)
	{
		if (ir.returnType().typeCategory != TypeCategory::Bool)
			log::fatal("Binary operator `$ $ $` cannot be evaluated.", left.type(), ir.binaryExpressionType(), right.type());

		return evaluateIntrinsicBinaryOperator<Left, Right, bool, _charOperation>(ir, left, right, state);
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
}
