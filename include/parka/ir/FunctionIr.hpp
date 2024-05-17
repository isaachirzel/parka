#ifndef PARKA_IR_FUNCTION_HPP
#define PARKA_IR_FUNCTION_HPP

#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	class FunctionIr: public LValueIr
	{
		String _symbol;
		PrototypeIr _prototype;
		BlockStatementIr* _body;

	public:

		FunctionIr(String&& symbol, PrototypeIr&& prototype, BlockStatementIr* body):
			LValueIr(ResolvableType::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype)),
			_body(body)
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		void setBody(BlockStatementIr& body)
		{
			assert(!_body);

			_body = &body;
		}

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return TypeIr::functionType; }
		const auto& prototype() const { return _prototype; }
		bool hasBody() const { return !!_body; }
		const auto& body() const { assert(_body); return *_body; }
	};
}

#endif
