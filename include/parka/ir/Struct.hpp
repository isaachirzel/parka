#ifndef PARKA_IR_STRUCT_HPP
#define PARKA_IR_STRUCT_HPP

#include "parka/symbol/Resolution.hpp"

namespace parka::ir
{
	class StructIr: public Resolution
	{
		String _symbol;

	public:

		StructIr(String&& symbol) :
		Resolution(ResolvableType::Struct),
		_symbol(std::move(symbol))
		{}
		StructIr(StructIr&&) = default;
		StructIr(const StructIr&) = delete;

		static StructIr *validate();
		
		const String& symbol() const { return _symbol; }
		const ValueType *valueType() const;
	};
}

#endif
