#include "parka/validation/F32TypeContext.hpp"

namespace parka::validation
{
	F32TypeContext F32TypeContext::instance;

	ir::BinaryOperatorIr* F32TypeContext::getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const
	{
		return nullptr;
	}

	ir::AssignmentOperatorIr* F32TypeContext::getAssignmentOperator(AssignmentType, const ir::TypeIr&) const
	{
		return nullptr;
	}
}
