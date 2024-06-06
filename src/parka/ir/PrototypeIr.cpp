#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	PrototypeIr::PrototypeIr(Array<ParameterIr*>&& parameters, const TypeIr& returnType):
		TypeIr(TypeCategory::Function),
		_parameters(std::move(parameters)),
		_returnType(returnType)
	{}

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

	bool PrototypeIr::operator==(const PrototypeIr& other) const
	{
		if (other.typeCategory != TypeCategory::Function)
			return false;

		if (_parameters.length() != other.parameters().length())
			return false;

		usize parameterCount = _parameters.length();

		for (usize i = 0; i < parameterCount; ++i)
		{
			auto& a = *_parameters[i];
			auto& b = *other.parameters()[i];

			if (a.type() != b.type())
				return false;
		}

		return true;
	}

	bool PrototypeIr::operator!=(const PrototypeIr& other) const
	{
		return !(*this == other);
	}
}
