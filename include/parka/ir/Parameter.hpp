#ifndef PARKA_IR_PARAMETER_HPP
#define PARKA_IR_PARAMETER_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/LValue.hpp"
#include "parka/ir/Type.hpp"

namespace parka::ir
{
	class ParameterIr: public LValue
	{
		String _symbol;
		Type _type;

	public:

		ParameterIr(Type&& type):
			LValue(ResolvableType::Parameter),
			_type(std::move(type))
		{}
		ParameterIr(ParameterIr&&) = default;
		ParameterIr(const ParameterIr&) = delete;

		const String& symbol() const { return _symbol; }
		const Type& type() const { return _type; }
	};
}

#endif
