#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/LValueIr.hpp"

namespace parka::ir
{
	class FunctionIr: public LValueIr, public TypeIr
	{
		String _symbol;
		CallOperatorIr _callOperator;

	public:

		static FunctionIr printFunction;

	public:

		FunctionIr(String symbol, CallOperatorIr&& callOperator):
			LValueIr(ResolvableType::Function),
			TypeIr(TypeCategory::Function),
			_symbol(std::move(symbol)),
			_callOperator(std::move(callOperator))
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		void setCallOperator(CallOperatorIr&& callOperator)
		{
			_callOperator = std::move(callOperator);
		}

		CallOperatorIr* getCallOperator(const Array<ExpressionIr*>&) const;
		std::ostream& printType(std::ostream& out) const;

		bool operator==(const TypeIr& other) const;
		bool operator!=(const TypeIr& other) const;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return *this; }
		const auto& prototype() const { return _prototype; }
		bool hasCallOperator() const { return _callOperator; }
		const auto& callOperator() const { assert(_callOperator); return *_callOperator; }
	};
}

#endif
