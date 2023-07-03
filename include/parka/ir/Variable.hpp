#ifndef PARKA_IR_VARIABLE_HPP
#define PARKA_IR_VARIABLE_HPP

#include "parka/symbol/Resolution.hpp"
#include "parka/ir/Value.hpp"

namespace parka::ir
{
	class VariableIr: public Resolution, public Value
	{
		String _symbol;
		Type _type;
	
	public:

		VariableIr(String&& symbol, Type&& type):
		Resolution(ResolvableType::Variable),
		_symbol(std::move(symbol)),
		_type(std::move(type))
		{}
		VariableIr(VariableIr&&) = default;
		VariableIr(const VariableIr&) = delete;

		const String& symbol() const { return _symbol; }
		const Type& valueType() const { return _type; }
	};
}

#endif
