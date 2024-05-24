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
	void addIntegerOperator(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators, BinaryExpressionType binaryExpressionType)
	{
		addBinaryOperatorWithLiteral<T, Integer, Return>(operators, binaryExpressionType);
	}

	template <typename T,  typename Return = T>
	void addFloatOperator(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators, BinaryExpressionType binaryExpressionType)
	{
		addBinaryOperatorWithLiteral<T, Float, Return>(operators, binaryExpressionType);
	}

	template <typename T>
	void addIntegerOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addIntegerOperator<T>(operators, BinaryExpressionType::Add);
		addIntegerOperator<T>(operators, BinaryExpressionType::Subtract);
		addIntegerOperator<T>(operators, BinaryExpressionType::Multiply);
		addIntegerOperator<T>(operators, BinaryExpressionType::Divide);
		addIntegerOperator<T>(operators, BinaryExpressionType::Modulus);
		addIntegerOperator<T>(operators, BinaryExpressionType::BitwiseOr);
		addIntegerOperator<T>(operators, BinaryExpressionType::BitwiseXor);
		addIntegerOperator<T>(operators, BinaryExpressionType::BitwiseAnd);
		addIntegerOperator<T>(operators, BinaryExpressionType::LeftShift);
		addIntegerOperator<T>(operators, BinaryExpressionType::RightShift);
		addIntegerOperator<T, bool>(operators, BinaryExpressionType::LessThan);
		addIntegerOperator<T, bool>(operators, BinaryExpressionType::GreaterThan);
		addIntegerOperator<T, bool>(operators, BinaryExpressionType::LessThanOrEqualTo);
		addIntegerOperator<T, bool>(operators, BinaryExpressionType::GreaterThanOrEqualTo);
		addIntegerOperator<T, bool>(operators, BinaryExpressionType::Equals);
		addIntegerOperator<T, bool>(operators, BinaryExpressionType::NotEquals);

	}

	template <typename T>
	void addFloatOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addFloatOperator<T>(operators, BinaryExpressionType::Add);
		addFloatOperator<T>(operators, BinaryExpressionType::Subtract);
		addFloatOperator<T>(operators, BinaryExpressionType::Multiply);
		addFloatOperator<T>(operators, BinaryExpressionType::Divide);
		addFloatOperator<T, bool>(operators, BinaryExpressionType::LessThan);
		addFloatOperator<T, bool>(operators, BinaryExpressionType::GreaterThan);
		addFloatOperator<T, bool>(operators, BinaryExpressionType::LessThanOrEqualTo);
		addFloatOperator<T, bool>(operators, BinaryExpressionType::GreaterThanOrEqualTo);
		addFloatOperator<T, bool>(operators, BinaryExpressionType::Equals);
		addFloatOperator<T, bool>(operators, BinaryExpressionType::NotEquals);
	}

	void addBoolOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::Equals);
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::NotEquals);
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::BooleanAnd);
		addBinaryOperator<bool, bool, bool>(operators, BinaryExpressionType::BooleanOr);
	}

	void addCharOperators(FlatMap<BinaryOperatorKey, BinaryOperatorIr*>& operators)
	{
		addBinaryOperator<char, char, bool>(operators, BinaryExpressionType::Equals);
		addBinaryOperator<char, char, bool>(operators, BinaryExpressionType::NotEquals);
	}

	FlatMap<BinaryOperatorKey, BinaryOperatorIr*> BinaryOperatorIr::getIntrinsicBinaryOperators()
	{
		auto operators = FlatMap<BinaryOperatorKey, BinaryOperatorIr*>(512);

		addIntegerOperators<Integer>(operators);
		addIntegerOperators<u8>(operators);
		addIntegerOperators<u16>(operators);
		addIntegerOperators<u32>(operators);
		addIntegerOperators<u64>(operators);
		addIntegerOperators<i8>(operators);
		addIntegerOperators<i16>(operators);
		addIntegerOperators<i32>(operators);
		addIntegerOperators<i64>(operators);
		addFloatOperators<Float>(operators);
		addFloatOperators<f32>(operators);
		addFloatOperators<f64>(operators);
		addBoolOperators(operators);
		addCharOperators(operators);

		return operators;
	}

	BinaryOperatorIr::BinaryOperatorIr(BinaryExpressionType binaryExpressionType, const TypeIr& leftType, const TypeIr& rightType, const TypeIr& returnType):
		_leftType(leftType),
		_rightType(rightType),
		_returnType(returnType),
		_binaryExpressionType(binaryExpressionType)
	{}
}
