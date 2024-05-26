#include "parka/evaluation/IntrinsicBinaryOperator.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"
#include <cstring>
#include <stdexcept>

namespace parka::evaluation
{
	// template <typename Left, typename Right, typename Return, Return (*operation)(const Left&, const Right&)>
	// Value& op(Value& left, Value& right, LocalState& state)
	// {
	// 	const auto& l = left.getValue<Left>();
	// 	const auto& r = right.getValue<Right>();
	// 	const Return ret = operation(l, r);
	// 	const auto& valueType = ir::TypeIr::of<Return>();
	// 	auto& result = state.pushValue(valueType);

	// 	result.setValue(ret);

	// 	return result;
	// }

	// template <typename Left, typename Right, typename Return, BinaryExpressionType binaryExpressionType>
	// inline Return _operation(const Left& l, const Right& r)
	// {
	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Add)
	// 		return (Return)(l + (Left)r);
		
	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Subtract)
	// 		return Return(l - (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Multiply)
	// 		return Return(l * (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Divide)
	// 		return Return(l / (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Modulus)
	// 		return Return(l % (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::BitwiseOr)
	// 		return Return(l | (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::BitwiseXor)
	// 		return Return(l ^ (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::BitwiseAnd)
	// 		return Return(l & (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Subtract)
	// 		return Return(l - (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::LeftShift)
	// 		return Return(l << (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::RightShift)
	// 		return Return(l >> (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::LessThan)
	// 		return Return(l < (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::GreaterThan)
	// 		return Return(l > (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::LessThanOrEqualTo)
	// 		return Return(l <= (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::GreaterThanOrEqualTo)
	// 		return Return(l >= (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Subtract)
	// 		return Return(l - (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::Equals)
	// 		return Return(l == (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::NotEquals)
	// 		return Return(l != (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::BooleanOr)
	// 		return Return(l || (Left)r);

	// 	if constexpr (binaryExpressionType == BinaryExpressionType::BooleanAnd)
	// 		return Return(l && (Left)r);

	// 	throw std::runtime_error("Invalid operation type.");
	// }

	// template <typename Left, typename Right>
	// validation::BinaryOperatorKey key(BinaryExpressionType binaryExpressionType)
	// {
	// 	const auto& left = ir::TypeIr::of<Left>();
	// 	const auto& right = ir::TypeIr::of<Right>();
	// 	auto key = validation::BinaryOperatorKey(left, right, binaryExpressionType);
		
	// 	return key;
	// }

	// template <typename Left, typename Right, typename Return, BinaryExpressionType binaryExpressionType>
	// void addBinaryOperator(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	auto k = key<Left, Right>(binaryExpressionType);
	// 	auto v = op<Left, Right, Return, _operation<Left, Right, Return, binaryExpressionType>>;

	// 	operators.insert(k, v);
	// }

	// template <typename T, typename Literal, typename Return = T, BinaryExpressionType binaryExpressionType>
	// void addBinaryOperatorWithLiteral(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addBinaryOperator<T, T, Return, binaryExpressionType>(operators);

	// 	if constexpr (!std::is_same_v<T, Literal>)
	// 	{
	// 		addBinaryOperator<T, Literal, Return, binaryExpressionType>(operators);
	// 		addBinaryOperator<Literal, T, Return, binaryExpressionType>(operators);
	// 	}
	// }

	// template <typename T, typename Return, BinaryExpressionType binaryExpressionType>
	// void addIntegerOperator(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addBinaryOperatorWithLiteral<T, Integer, Return, binaryExpressionType>(operators);
	// }

	// template <typename T,  typename Return, BinaryExpressionType binaryExpressionType>
	// void addFloatOperator(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addBinaryOperatorWithLiteral<T, Float, Return, binaryExpressionType>(operators);
	// }

	// template <typename T>
	// void addIntegerOperators(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addIntegerOperator<T, T, BinaryExpressionType::Add>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::Subtract>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::Multiply>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::Divide>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::Modulus>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::BitwiseOr>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::BitwiseXor>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::BitwiseAnd>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::LeftShift>(operators);
	// 	addIntegerOperator<T, T, BinaryExpressionType::RightShift>(operators);
	// 	addIntegerOperator<T, bool, BinaryExpressionType::LessThan>(operators);
	// 	addIntegerOperator<T, bool, BinaryExpressionType::GreaterThan>(operators);
	// 	addIntegerOperator<T, bool, BinaryExpressionType::LessThanOrEqualTo>(operators);
	// 	addIntegerOperator<T, bool, BinaryExpressionType::GreaterThanOrEqualTo>(operators);
	// 	addIntegerOperator<T, bool, BinaryExpressionType::Equals>(operators);
	// 	addIntegerOperator<T, bool, BinaryExpressionType::NotEquals>(operators);

	// }

	// template <typename T>
	// void addFloatOperators(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addFloatOperator<T, T, BinaryExpressionType::Add>(operators);
	// 	addFloatOperator<T, T, BinaryExpressionType::Subtract>(operators);
	// 	addFloatOperator<T, T, BinaryExpressionType::Multiply>(operators);
	// 	addFloatOperator<T, T, BinaryExpressionType::Divide>(operators);
	// 	addFloatOperator<T, bool, BinaryExpressionType::LessThan>(operators);
	// 	addFloatOperator<T, bool, BinaryExpressionType::GreaterThan>(operators);
	// 	addFloatOperator<T, bool, BinaryExpressionType::LessThanOrEqualTo>(operators);
	// 	addFloatOperator<T, bool, BinaryExpressionType::GreaterThanOrEqualTo>(operators);
	// 	addFloatOperator<T, bool, BinaryExpressionType::Equals>(operators);
	// 	addFloatOperator<T, bool, BinaryExpressionType::NotEquals>(operators);
	// }

	// void addBoolOperators(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addBinaryOperator<bool, bool, bool, BinaryExpressionType::Equals>(operators);
	// 	addBinaryOperator<bool, bool, bool, BinaryExpressionType::NotEquals>(operators);
	// 	addBinaryOperator<bool, bool, bool, BinaryExpressionType::BooleanAnd>(operators);
	// 	addBinaryOperator<bool, bool, bool, BinaryExpressionType::BooleanOr>(operators);
	// }

	// void addCharOperators(FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>& operators)
	// {
	// 	addBinaryOperator<char, char, bool, BinaryExpressionType::Equals>(operators);
	// 	addBinaryOperator<char, char, bool, BinaryExpressionType::NotEquals>(operators);
	// }
	
	// FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator> getIntrinsicBinaryOperators()
	// {
	// 	auto operators = FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator>(256);

	// 	addIntegerOperators<Integer>(operators);
	// 	addIntegerOperators<u8>(operators);
	// 	addIntegerOperators<u16>(operators);
	// 	addIntegerOperators<u32>(operators);
	// 	addIntegerOperators<u64>(operators);
	// 	addIntegerOperators<i8>(operators);
	// 	addIntegerOperators<i16>(operators);
	// 	addIntegerOperators<i32>(operators);
	// 	addIntegerOperators<i64>(operators);
	// 	addFloatOperators<Float>(operators);
	// 	addFloatOperators<f32>(operators);
	// 	addFloatOperators<f64>(operators);
	// 	addBoolOperators(operators);
	// 	addCharOperators(operators);

	// 	return operators;
	// }
}
