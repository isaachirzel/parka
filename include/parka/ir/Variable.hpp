#ifndef PARKA_IR_VARIABLE_HPP
#define PARKA_IR_VARIABLE_HPP

#include "parka/ir/LValue.hpp"
#include "parka/ir/Type.hpp"

namespace parka::ir
{
	class VariableIr: public LValue
	{
		String _symbol;
		Type _type;
	
	public:

		VariableIr(String&& symbol, Type&& type):
			LValue(ResolvableType::Variable),
			_symbol(std::move(symbol)),
			_type(std::move(type))
		{}
		VariableIr(VariableIr&&) = default;
		VariableIr(const VariableIr&) = delete;

		const String& symbol() const { return _symbol; }
		const Type& type() const { return _type; }
	};
}

#endif
