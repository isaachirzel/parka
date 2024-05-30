#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	PrototypeIr::PrototypeIr(Array<ParameterIr*>&& parameters, const TypeIr& returnType):
		TypeIr(TypeCategory::Function),
		_parameters(std::move(parameters)),
		_returnType(returnType)
	{}

	// const CallOperatorIr* PrototypeIr::getCallOperator(const Array<ExpressionIr*>& arguments) const
	// {

	// }

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
