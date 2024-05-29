#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	class FunctionIr: public LValueIr, public TypeIr
	{
		String _symbol;
		PrototypeIr _prototype;

	public:

		static FunctionIr printFunction;

	public:

		FunctionIr(String symbol, PrototypeIr&& prototype):
			LValueIr(ResolvableType::Function),
			TypeIr(TypeCategory::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype))
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		CallOperatorIr* getCallOperator(const Array<ExpressionIr*>&) const;
		std::ostream& printType(std::ostream& out) const;

		bool operator==(const TypeIr& other) const;
		bool operator!=(const TypeIr& other) const;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return *this; }
		const auto& prototype() const { return _prototype; }
	};
}

#endif
