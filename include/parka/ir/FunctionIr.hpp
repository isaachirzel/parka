#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	class FunctionIr: public EntityIr
	{
		String _symbol;
		PrototypeIr _prototype;
		
	public:

		static FunctionIr printFunction;

	public:

		FunctionIr(String symbol, PrototypeIr&& prototype):
			EntityIr(ResolvableType::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype))
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		const String& symbol() const { return _symbol; }
		const auto& prototype() const { return _prototype; }
		const TypeIr& type() const { return _prototype; }
	};
}

#endif
