#ifndef PARKA_IR_INTRINSIC_FUNCTION_IR_HPP
#define PARKA_IR_INTRINSIC_FUNCTION_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	class IntrinsicFunctionIr: public LValueIr
	{
		String _symbol;
		PrototypeIr _prototype;

	public:

		static IntrinsicFunctionIr printFunction;

	public:

		IntrinsicFunctionIr(String&& symbol, PrototypeIr&& prototype):
			LValueIr(ResolvableType::IntrinsicFunction),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype))
		{}
		IntrinsicFunctionIr(IntrinsicFunctionIr&&) = default;
		IntrinsicFunctionIr(const IntrinsicFunctionIr&) = delete;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return TypeIr::functionType; }
		const auto& prototype() const { return _prototype; }
	};
}

#endif
