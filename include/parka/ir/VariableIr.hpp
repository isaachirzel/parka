#ifndef PARKA_IR_VARIABLE_HPP
#define PARKA_IR_VARIABLE_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class VariableIr: public LValueIr
	{
		String _symbol;
		TypeIr _type;
	
	public:

		VariableIr(String&& symbol, TypeIr&& type):
			LValueIr(ResolvableType::Variable),
			_symbol(std::move(symbol)),
			_type(std::move(type))
		{}
		VariableIr(VariableIr&&) = default;
		VariableIr(const VariableIr&) = delete;

		void setType(const TypeIr& type) { _type = type; }

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return _type; }
	};
}

#endif
