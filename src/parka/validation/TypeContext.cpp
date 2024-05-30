#include "parka/validation/TypeContext.hpp"
#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/validation/GlobalContext.hpp"

namespace parka::validation
{
	ir::ConversionIr* TypeContext::getConversionTo(const ir::TypeIr&) const
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

	void TypeContext::addCallOperator(ir::CallOperatorIr&& callOperator)
	{
		// TODO: Validate this
		_callOperators.push(std::move(callOperator));
	}

	static bool isCompatible(const Array<ir::ExpressionIr*>& arguments, const ir::CallOperatorIr& op, GlobalContext& globalContext)
	{
		const auto& parameters = op.prototype().parameters();
		
		if (arguments.length() != parameters.length())
			return false;

		for (usize i = 0; i < parameters.length(); ++i)
		{
			auto& parameter = *parameters[i];
			auto& argument = *arguments[i];
			auto& typeContext = globalContext.getTypeContext(argument.type());
			auto* conversion = typeContext.getConversionTo(parameter.type());

			if (!conversion)
				return false;
		}

		return true;
	}

	const ir::CallOperatorIr* TypeContext::getCallOperator(const Array<ir::ExpressionIr*>& arguments) const
	{

		for (const auto& op : _callOperators)
		{
			if (isCompatible(arguments, op, _globalContext))
				return &op;
		}

		return nullptr;
	}
}
