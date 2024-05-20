#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ir
{
	class FunctionIr: public LValueIr
	{
		String _symbol;
		PrototypeIr _prototype;
		Optional<FunctionBodyIr> _body;

	public:

		FunctionIr(String&& symbol, PrototypeIr&& prototype, Optional<FunctionBodyIr>&& body):
			LValueIr(ResolvableType::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype)),
			_body(std::move(body))
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		void setBody(FunctionBodyIr&& body)
		{
			_body = std::move(body);
		}

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return TypeIr::functionType; }
		const auto& prototype() const { return _prototype; }
		bool hasBody() const { return !!_body; }
		const auto& body() const { assert(_body); return *_body; }
	};
}

#endif
