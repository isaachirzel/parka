#ifndef PARKA_IR_VARIABLE_HPP
#define PARKA_IR_VARIABLE_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class VariableIr: public EntityIr
	{
		String _symbol;
		const TypeIr* _type;
	
	public:

		VariableIr(String&& symbol, const TypeIr& type):
			EntityIr(ResolvableType::Variable),
			_symbol(std::move(symbol)),
			_type(&type)
		{}
		VariableIr(VariableIr&&) = default;
		VariableIr(const VariableIr&) = delete;

		void setType(const TypeIr& type) { _type = &type; }

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return *_type; }
	};
}

#endif
