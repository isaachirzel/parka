#include "parka/evaluation/IntrinsicAssignmentOperator.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/validation/AssignmentOperatorKey.hpp"

namespace parka::evaluation
{
	// template <typename Left, typename Right, void (*operation)(Left&, const Right&)>
	// void op(Value& left, const Value& right)
	// {
	// 	auto& l = left.getValue<Left>();
	// 	const auto& r = right.getValue<Right>();

	// 	operation(l, r);
	// }

	// template <typename Left, typename Right, AssignmentType binaryExpressionType>
	// inline void _operation(Left& l, const Right& r)
	// {
	// 	if constexpr (binaryExpressionType == AssignmentType::Assign)
	// 	{
	// 		l = (Left)r;
	// 		return;
	// 	}	

	// 	if constexpr (binaryExpressionType == AssignmentType::AddAssign)
	// 	{
	// 		l += (Left)r;
	// 		return;
	// 	}
		
	// 	if constexpr (binaryExpressionType == AssignmentType::SubtractAssign)
	// 	{
	// 		l -= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::MultiplyAssign)
	// 	{
	// 		l *= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::DivideAssign)
	// 	{
	// 		l /= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::ModulusAssign)
	// 	{
	// 		l %= (Left)r;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::LeftShiftAssign)
	// 	{
	// 		l <<= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::RightShiftAssign)
	// 	{
	// 		l >>= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::BitwiseOrAssign)
	// 	{
	// 		l |= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::BitwiseXorAssign)
	// 	{
	// 		l ^= (Left)r;
	// 		return;
	// 	}

	// 	if constexpr (binaryExpressionType == AssignmentType::BitwiseAndAssign)
	// 	{
	// 		l &= (Left)r;
	// 		return;
	// 	}

	// 	throw std::runtime_error("Invalid operation type.");
	// }

	// template <typename Left, typename Right>
	// validation::AssignmentOperatorKey key(AssignmentType assignmentType)
	// {
	// 	const auto& left = ir::TypeIr::of<Left>();
	// 	const auto& right = ir::TypeIr::of<Right>();
	// 	auto key = validation::AssignmentOperatorKey(left, right, assignmentType);
		
	// 	return key;
	// }

	// template <typename Left, typename Right, AssignmentType assignmentType>
	// void addAssignmentOperator(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	auto k = key<Left, Right>(assignmentType);
	// 	auto v = op<Left, Right, _operation<Left, Right, assignmentType>>;

	// 	operators.insert(k, v);
	// }

	// template <typename T, typename Literal, AssignmentType assignmentType>
	// void addAssignmentOperatorWithLiteral(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addAssignmentOperator<T, T, assignmentType>(operators);

	// 	if constexpr (!std::is_same_v<T, Literal>)
	// 		addAssignmentOperator<T, Literal, assignmentType>(operators);
	// }

	// template <typename T, AssignmentType assignmentType>
	// void addIntegerAssignmentOperator(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addAssignmentOperatorWithLiteral<T, Integer, assignmentType>(operators);
	// }

	// template <typename T, AssignmentType assignmentType>
	// void addFloatAssignmentOperator(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addAssignmentOperatorWithLiteral<T, Float, assignmentType>(operators);
	// }

	// template <typename T>
	// void addIntegerAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addIntegerAssignmentOperator<T, AssignmentType::Assign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::AddAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::SubtractAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::MultiplyAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::DivideAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::ModulusAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::LeftShiftAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::RightShiftAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::BitwiseOrAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::BitwiseXorAssign>(operators);
	// 	addIntegerAssignmentOperator<T, AssignmentType::BitwiseAndAssign>(operators);
	// }

	// template <typename T>
	// void addFloatAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addFloatAssignmentOperator<T, AssignmentType::Assign>(operators);
	// 	addFloatAssignmentOperator<T, AssignmentType::AddAssign>(operators);
	// 	addFloatAssignmentOperator<T, AssignmentType::SubtractAssign>(operators);
	// 	addFloatAssignmentOperator<T, AssignmentType::MultiplyAssign>(operators);
	// 	addFloatAssignmentOperator<T, AssignmentType::DivideAssign>(operators);
	// }

	// void addBoolAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addAssignmentOperator<bool, bool, AssignmentType::Assign>(operators);
	// }

	// void addCharAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>& operators)
	// {
	// 	addAssignmentOperator<char, char, AssignmentType::Assign>(operators);
	// }

	// FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator> getIntrinsicAssignmentOperators()
	// {
	// 	auto operators = FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator>(128);

	// 	addIntegerAssignmentOperators<u8>(operators);
	// 	addIntegerAssignmentOperators<u16>(operators);
	// 	addIntegerAssignmentOperators<u32>(operators);
	// 	addIntegerAssignmentOperators<u64>(operators);
	// 	addIntegerAssignmentOperators<i8>(operators);
	// 	addIntegerAssignmentOperators<i16>(operators);
	// 	addIntegerAssignmentOperators<i32>(operators);
	// 	addIntegerAssignmentOperators<i64>(operators);
	// 	addFloatAssignmentOperators<f32>(operators);
	// 	addFloatAssignmentOperators<f64>(operators);
	// 	addBoolAssignmentOperators(operators);
	// 	addCharAssignmentOperators(operators);

	// 	return operators;
	// }
}
