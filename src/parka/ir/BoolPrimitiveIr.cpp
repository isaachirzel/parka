#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"

namespace parka::ir
{
	BoolPrimitiveIr BoolPrimitiveIr::instance;

	BinaryOperatorIr equalsBinaryOperator(BinaryExpressionType::Equals, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);
	BinaryOperatorIr notEqualsBinaryOperator(BinaryExpressionType::NotEquals, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);
	BinaryOperatorIr booleanOrBinaryOperator(BinaryExpressionType::BooleanOr, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);
	BinaryOperatorIr booleanAndBinaryOperator(BinaryExpressionType::BooleanAnd, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);

	BoolPrimitiveIr::BoolPrimitiveIr():
		TypeIr(TypeCategory::Bool),
		EntityIr(ResolvableType::Primitive),
		_symbol("bool")
	{}

	// BinaryOperatorIr* BoolPrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& rhs) const
	// {
	// 	if (&rhs != &instance)
	// 		return nullptr;

	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Equals:
	// 			return &binop<BinaryExpressionType::Equals, bool>();

	// 		case BinaryExpressionType::NotEquals:
	// 			return &binop<BinaryExpressionType::NotEquals, bool>();

	// 		case BinaryExpressionType::BooleanOr:
	// 			return &binop<BinaryExpressionType::BooleanOr, bool>();

	// 		case BinaryExpressionType::BooleanAnd:
	// 			return &binop<BinaryExpressionType::BooleanAnd, bool>();

	// 		default:
	// 			break;
	// 	}

	// 	return nullptr;
	// }

	// AssignmentOperatorIr* BoolPrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	// {
	// 	if (other == *this && assignmentType == AssignmentType::Assign)
	// 		return &assgn<AssignmentType::Assign, bool>();

	// 	return nullptr;
	// }

	std::ostream& BoolPrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
