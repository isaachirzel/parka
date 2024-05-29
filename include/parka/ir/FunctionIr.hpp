#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/InvalidTypeIr.hpp"
#include "parka/ir/EntityIr.hpp"

namespace parka::ir
{
	class FunctionIr: public EntityIr
	{
		String _symbol;

	public:

		static FunctionIr printFunction;

	public:

		FunctionIr(String symbol):
			EntityIr(ResolvableType::Function),
			_symbol(std::move(symbol))
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::functionType; }
	};
}

#endif
