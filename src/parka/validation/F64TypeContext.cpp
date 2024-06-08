#include "parka/validation/F64TypeContext.hpp"

namespace parka::validation
{
	F64TypeContext F64TypeContext::instance;

	ir::BinaryOperatorIr* F64TypeContext::getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const
	{
		return nullptr;
	}

	ir::AssignmentOperatorIr* F64TypeContext::getAssignmentOperator(AssignmentType, const ir::TypeIr&) const
	{
		return nullptr;
	}
}
