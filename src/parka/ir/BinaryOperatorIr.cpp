#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/symbol/BinaryOperatorKey.hpp"
#include "parka/util/Integer.hpp"
#include <type_traits>

namespace parka::ir
{
	template <typename Left, typename Right, typename Return>
	BinaryOperatorIr* op(BinaryExpressionType binaryExpressionType)
	{
		const auto& left = ir::TypeIr::of<Left>();
		const auto& right = ir::TypeIr::of<Right>();
		const auto& ret = ir::TypeIr::of<Return>();
		auto* op = new BinaryOperatorIr(binaryExpressionType, left, right, ret);
		
		return op;
	}

	template <typename Left, typename Right>
	BinaryOperatorKey key(BinaryExpressionType binaryExpressionType)
	{
		const auto& left = ir::TypeIr::of<Left>();
		const auto& right = ir::TypeIr::of<Right>();
		auto key = BinaryOperatorKey(left, right, binaryExpressionType);
		
		return key;
	}

	template <typename Left, typename Right, typename Return>
	void addBinaryOperator(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators, BinaryExpressionType binaryExpressionType)
	{
		auto k = key<Left, Right>(binaryExpressionType);
		auto v = op<Left, Right, Return>(binaryExpressionType);

		operators.insert(k, v);
	}

	template <typename T, typename Literal, typename Return = T>
	void addBinaryOperatorWithLiteral(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators, BinaryExpressionType binaryExpressionType)
	{
		addBinaryOperator<T, T, Return>(operators, binaryExpressionType);

		if constexpr (!std::is_same_v<T, Literal>)
		{
			addBinaryOperator<T, Literal, Return>(operators, binaryExpressionType);
			addBinaryOperator<Literal, T, Return>(operators, binaryExpressionType);
		}
	}

	template <typename T, typename Return = T>
	void addIntegerBinaryOperator(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators, BinaryExpressionType binaryExpressionType)
	{
		addBinaryOperatorWithLiteral<T, Integer, Return>(operators, binaryExpressionType);
	}

	template <typename T,  typename Return = T>
	void addFloatBinaryOperator(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators, BinaryExpressionType binaryExpressionType)
	{
		addBinaryOperatorWithLiteral<T, Float, Return>(operators, binaryExpressionType);
	}

	template <typename T>
	void addIntegerBinaryOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::Add);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::Subtract);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::Multiply);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::Divide);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::Modulus);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::BitwiseOr);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::BitwiseXor);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::BitwiseAnd);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::LeftShift);
		addIntegerBinaryOperator<T>(operators, BinaryExpressionType::RightShift);
		addIntegerBinaryOperator<T, bool>(operators, BinaryExpressionType::LessThan);
		addIntegerBinaryOperator<T, bool>(operators, BinaryExpressionType::GreaterThan);
		addIntegerBinaryOperator<T, bool>(operators, BinaryExpressionType::LessThanOrEqualTo);
		addIntegerBinaryOperator<T, bool>(operators, BinaryExpressionType::GreaterThanOrEqualTo);
		addIntegerBinaryOperator<T, bool>(operators, BinaryExpressionType::Equals);
		addIntegerBinaryOperator<T, bool>(operators, BinaryExpressionType::NotEquals);

	}

	template <typename T>
	void addFloatBinaryOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addFloatBinaryOperator<T>(operators, BinaryExpressionType::Add);
		addFloatBinaryOperator<T>(operators, BinaryExpressionType::Subtract);
		addFloatBinaryOperator<T>(operators, BinaryExpressionType::Multiply);
		addFloatBinaryOperator<T>(operators, BinaryExpressionType::Divide);
		addFloatBinaryOperator<T, bool>(operators, BinaryExpressionType::LessThan);
		addFloatBinaryOperator<T, bool>(operators, BinaryExpressionType::GreaterThan);
		addFloatBinaryOperator<T, bool>(operators, BinaryExpressionType::LessThanOrEqualTo);
		addFloatBinaryOperator<T, bool>(operators, BinaryExpressionType::GreaterThanOrEqualTo);
		addFloatBinaryOperator<T, bool>(operators, BinaryExpressionType::Equals);
		addFloatBinaryOperator<T, bool>(operators, BinaryExpressionType::NotEquals);
	}

	void addBoolBinaryOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::Equals);
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::NotEquals);
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::BooleanAnd);
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::BooleanOr);
	}

	void addCharBinaryOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addBinaryOperator<char, char, bool>(operators, BinaryExpressionType::Equals);
		addBinaryOperator<char, char, bool>(operators, BinaryExpressionType::NotEquals);
	}

	FlatMap<BinaryOperatorKey, BinaryOperatorIr*> BinaryOperatorIr::getIntrinsicBinaryOperators()
	{
		auto operators = FlatMap<BinaryOperatorKey, BinaryOperatorIr*>(512);

		addIntegerBinaryOperators<Integer>(operators);
		addIntegerBinaryOperators<u8>(operators);
		addIntegerBinaryOperators<u16>(operators);
		addIntegerBinaryOperators<u32>(operators);
		addIntegerBinaryOperators<u64>(operators);
		addIntegerBinaryOperators<i8>(operators);
		addIntegerBinaryOperators<i16>(operators);
		addIntegerBinaryOperators<i32>(operators);
		addIntegerBinaryOperators<i64>(operators);
		addFloatBinaryOperators<Float>(operators);
		addFloatBinaryOperators<f32>(operators);
		addFloatBinaryOperators<f64>(operators);
		addBoolBinaryOperators(operators);
		addCharBinaryOperators(operators);

		return operators;
	}

	BinaryOperatorIr::BinaryOperatorIr(BinaryExpressionType binaryExpressionType, const TypeIr& leftType, const TypeIr& rightType, const TypeIr& returnType):
		_leftType(leftType),
		_rightType(rightType),
		_returnType(returnType),
		_binaryExpressionType(binaryExpressionType)
	{}
}
