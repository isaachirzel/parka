#ifndef PARKA_IR_STRUCT_HPP
#define PARKA_IR_STRUCT_HPP

#include "parka/ir/Entity.hpp"

namespace parka::ir
{
	class StructIr : public EntityIr
	{
		String _symbol;

	public:

		StructIr(String&& symbol) :
		_symbol(std::move(symbol))
		{}
		StructIr(StructIr&&) = default;
		StructIr(const StructIr&) = delete;

		static StructIr *validate();
		
		EntityType type() const { return EntityType::Struct; }
		const String& symbol() const { return _symbol; }
		const ValueType *valueType() const;
	};
}

#endif
