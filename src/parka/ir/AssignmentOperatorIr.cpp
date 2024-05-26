#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/validation/AssignmentOperatorKey.hpp"

namespace parka::ir
{
	// template <typename Left, typename Right>
	// AssignmentOperatorIr* op(AssignmentType assignmentType)
	// {
	// 	const auto& left = ir::TypeIr::of<Left>();
	// 	const auto& right = ir::TypeIr::of<Right>();
	// 	auto* op = new AssignmentOperatorIr(left, right, assignmentType);
		
	// 	return op;
	// }

	// template <typename Left, typename Right>
	// validation::AssignmentOperatorKey key(AssignmentType assignmentType)
	// {
	// 	const auto& left = ir::TypeIr::of<Left>();
	// 	const auto& right = ir::TypeIr::of<Right>();
	// 	auto key = validation::AssignmentOperatorKey(left, right, assignmentType);
		
	// 	return key;
	// }

	// template <typename Left, typename Right>
	// void addAssignmentOperator(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators, AssignmentType assignmentType)
	// {
	// 	auto k = key<Left, Right>(assignmentType);
	// 	auto v = op<Left, Right>(assignmentType);

	// 	operators.insert(k, v);
	// }

	// template <typename T, typename Literal>
	// void addAssignmentOperatorWithLiteral(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators, AssignmentType assignmentType)
	// {
	// 	addAssignmentOperator<T, T>(operators, assignmentType);

	// 	if constexpr (!std::is_same_v<T, Literal>)
	// 		addAssignmentOperator<T, Literal>(operators, assignmentType);
	// }

	// template <typename T>
	// void addIntegerAssignmentOperator(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators, AssignmentType assignmentType)
	// {
	// 	addAssignmentOperatorWithLiteral<T, Integer>(operators, assignmentType);
	// }

	// template <typename T>
	// void addFloatAssignmentOperator(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators, AssignmentType assignmentType)
	// {
	// addAssignmentOperatorWithLiteral<T, Float>(operators, assignmentType);
	// }

	// template <typename T>
	// void addIntegerAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators)
	// {
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::Assign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::AddAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::SubtractAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::MultiplyAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::DivideAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::ModulusAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::LeftShiftAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::RightShiftAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::BitwiseOrAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::BitwiseXorAssign);
	// 	addIntegerAssignmentOperator<T>(operators, AssignmentType::BitwiseAndAssign);
	// }

	// template <typename T>
	// void addFloatAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators)
	// {
	// 	addFloatAssignmentOperator<T>(operators, AssignmentType::Assign);
	// 	addFloatAssignmentOperator<T>(operators, AssignmentType::AddAssign);
	// 	addFloatAssignmentOperator<T>(operators, AssignmentType::SubtractAssign);
	// 	addFloatAssignmentOperator<T>(operators, AssignmentType::MultiplyAssign);
	// 	addFloatAssignmentOperator<T>(operators, AssignmentType::DivideAssign);
	// }

	// void addBoolAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators)
	// {
	// 	addAssignmentOperator<bool, bool>(operators, AssignmentType::Assign);
	// }

	// void addCharAssignmentOperators(FlatMap<validation::AssignmentOperatorKey, AssignmentOperatorIr*>& operators)
	// {
	// 	addAssignmentOperator<char, char>(operators, AssignmentType::Assign);
	// }

	// FlatMap<validation::AssignmentOperatorKey, ir::AssignmentOperatorIr*> AssignmentOperatorIr::getIntrinsicAssignmentOperators()
	// {
	// 	auto operators = FlatMap<validation::AssignmentOperatorKey, ir::AssignmentOperatorIr*>(256);

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

	AssignmentOperatorIr::AssignmentOperatorIr(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType):
		_left(left),
		_right(right),
		_assignmentType(assignmentType)
	{}
}
