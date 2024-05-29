#ifndef PARKA_IR_STRUCT_HPP
#define PARKA_IR_STRUCT_HPP

#include "parka/ir/LValueIr.hpp"

namespace parka::ir
{
	class StructIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		StructIr(String&& symbol):
			TypeIr(TypeCategory::Struct),
			LValueIr(ResolvableType::Struct),
			_symbol(std::move(symbol))
		{}
		StructIr(StructIr&&) = default;
		StructIr(const StructIr&) = delete;
		
		const String& symbol() const { return _symbol; }
	};
}

#endif
