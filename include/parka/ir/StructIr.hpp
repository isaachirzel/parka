#ifndef PARKA_IR_STRUCT_HPP
#define PARKA_IR_STRUCT_HPP

#include "parka/ir/LValueIr.hpp"

namespace parka::ir
{
	class StructIr: public TypeBase, public LValueIr
	{
		String _symbol;

	public:

		StructIr(String&& symbol):
			LValueIr(ResolvableType::Struct),
			_symbol(std::move(symbol))
		{}
		StructIr(StructIr&&) = default;
		StructIr(const StructIr&) = delete;

		static StructIr *validate();
		
		const String& symbol() const { return _symbol; }
	};
}

#endif
