#ifndef PARKA_IR_PARAMETER_HPP
#define PARKA_IR_PARAMETER_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class ParameterIr: public LValueIr
	{
		String _symbol;
		TypeIr _type;

	public:

		ParameterIr(TypeIr&& type):
			LValueIr(ResolvableType::Parameter),
			_type(std::move(type))
		{}
		ParameterIr(ParameterIr&&) = default;
		ParameterIr(const ParameterIr&) = delete;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return _type; }
	};
}

#endif
