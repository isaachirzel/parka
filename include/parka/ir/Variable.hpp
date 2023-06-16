#ifndef PARKA_IR_VARIABLE_HPP
#define PARKA_IR_VARIABLE_HPP

#include "parka/ir/Entity.hpp"

namespace parka::ir
{
	class VariableIr: public EntityIr
	{
		String _symbol;
		ValueType _type;
	
	public:

		VariableIr(String&& symbol, ValueType&& type) :
		EntityIr(EntityType::Variable),
		_symbol(std::move(symbol)),
		_type(std::move(type))
		{}
		VariableIr(VariableIr&&) = default;
		VariableIr(const VariableIr&) = delete;

		const String& symbol() const { return _symbol; }
		const ValueType *valueType() const { return &_type; }
	};
}

#endif
