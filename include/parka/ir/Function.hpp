#ifndef PARKA_IR_FUNCTION_HPP
#define PARKA_IR_FUNCTION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/ir/LValue.hpp"
#include "parka/ir/Prototype.hpp"

namespace parka::ir
{
	class FunctionIr: public LValue
	{
		String _symbol;
		PrototypeIr _prototype;
		ExpressionIr& _body;

	public:

		FunctionIr(String&& symbol, PrototypeIr&& prototype, ExpressionIr& body):
			LValue(ResolvableType::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype)),
			_body(body)
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		const String& symbol() const { return _symbol; }
		const Type& type() const { return Type::functionType; }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};
}

#endif
