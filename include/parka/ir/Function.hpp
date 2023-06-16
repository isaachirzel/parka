#ifndef PARKA_IR_FUNCTION_HPP
#define PARKA_IR_FUNCTION_HPP

#include "parka/ir/Entity.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Prototype.hpp"

namespace parka::ir
{
	class FunctionIr : public EntityIr
	{
		String _symbol;
		PrototypeIr _prototype;
		ExpressionIr& _body;

	public:

		FunctionIr(String&& symbol, PrototypeIr&& prototype, ExpressionIr& body) :
		_symbol(std::move(symbol)),
		_prototype(std::move(prototype)),
		_body(body)
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		EntityType entityType() const { return EntityType::Function; }
		const ValueType *valueType() const;
		const String& symbol() const { return _symbol; }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};
}

#endif
