#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	ir::ConversionIr* TypeContext::getConversion(const ir::TypeIr&) const
	{
		return nullptr;
	}

	ir::BinaryOperatorIr* TypeContext::getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const
	{
		return nullptr;
	}

	ir::AssignmentOperatorIr* TypeContext::getAssignmentOperator(AssignmentType, const ir::TypeIr&) const
	{
		return nullptr;
	}

	const ir::CallOperatorIr* TypeContext::getCallOperator(const Array<ir::ExpressionIr*>&) const
	{
		return nullptr;
	}
}
