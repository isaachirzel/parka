#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	PrototypeIr::PrototypeIr(Array<ParameterIr*>&& parameters, const TypeIr& returnType, CallOperatorIr&& callOperator):
		TypeIr(TypeCategory::Function),
		_parameters(std::move(parameters)),
		_returnType(&returnType),
		_callOperator(std::move(callOperator))
	{}

	const CallOperatorIr* PrototypeIr::getCallOperator(const Array<ExpressionIr*>& arguments) const
	{
		if (arguments.length() != _parameters.length())
			return nullptr;

		for (usize i = 0; i < _parameters.length(); ++i)
		{
			auto& parameter = *_parameters[i];
			auto& argument = *arguments[i];
			auto* conversion = argument.type().getConversion(parameter.type());

			if (!conversion)
				return nullptr;
		}

		return &_callOperator;
	}

	std::ostream& PrototypeIr::printType(std::ostream& out) const
	{
		out << "(";
		
		for (usize i = 0; i < _parameters.length(); ++i)
		{
			if (i > 0)
				out << ", ";

			out << _parameters[i]->type();
		}

		out << "): " << _returnType;
		return out;
	}

	bool PrototypeIr::operator==(const TypeIr& other) const
	{
		if (other.typeCategory != TypeCategory::Function)
			return false;

		auto& otherPrototype = static_cast<const PrototypeIr&>(other);

		if (_parameters.length() != otherPrototype.parameters().length())
			return false;

		usize parameterCount = _parameters.length();

		for (usize i = 0; i < parameterCount; ++i)
		{
			auto& a = *_parameters[i];
			auto& b = *otherPrototype.parameters()[i];

			if (a.type() != b.type())
				return false;
		}

		return true;
	}

	bool PrototypeIr::operator!=(const TypeIr& other) const
	{
		return !(*this == other);
	}
}
