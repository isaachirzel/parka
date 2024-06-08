#include "parka/validation/FloatTypeContext.hpp"

namespace parka::validation
{
	FloatTypeContext FloatTypeContext::instance;

	ir::ConversionIr* FloatTypeContext::getConversionTo(const ir::TypeIr& to) const
	{
		return nullptr;
	}

	ir::BinaryOperatorIr* FloatTypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		return nullptr;
	}

	ir::AssignmentOperatorIr* FloatTypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		return nullptr;
	}
}
