#include "parka/ir/CharPrimitiveIr.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"

namespace parka::ir
{
	CharPrimitiveIr CharPrimitiveIr::instance;

	CharPrimitiveIr::CharPrimitiveIr():
		TypeIr(TypeCategory::Char),
		EntityIr(ResolvableType::Primitive),
		_symbol("char")
	{}

	BinaryOperatorIr* CharPrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	{
		if (other != *this)
			return nullptr;

		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return &binop<BinaryExpressionType::Equals, char>();

			case BinaryExpressionType::NotEquals:
				return &binop<BinaryExpressionType::NotEquals, char>();
			
			default:
				break;
		}

		return nullptr;
	}

	AssignmentOperatorIr* CharPrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	{
		if (other == *this && assignmentType == AssignmentType::Assign)
			return &assgn<AssignmentType::Assign, char>();
		
		return nullptr;
	}

	std::ostream& CharPrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
