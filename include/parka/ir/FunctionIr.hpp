#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ir
{
	class FunctionIr: public LValueIr, public TypeIr
	{
		String _symbol;
		PrototypeIr _prototype;
		Optional<FunctionBodyIr> _body;
		bool _isIntrinsic;

	public:

		static FunctionIr printFunction;

	public:

		FunctionIr(String&& symbol, PrototypeIr&& prototype):
			LValueIr(ResolvableType::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype)),
			_body(),
			_isIntrinsic(true)
		{}
		FunctionIr(String&& symbol, PrototypeIr&& prototype, Optional<FunctionBodyIr>&& body):
			LValueIr(ResolvableType::Function),
			_symbol(std::move(symbol)),
			_prototype(std::move(prototype)),
			_body(std::move(body)),
			_isIntrinsic(false)
		{}
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		void setBody(FunctionBodyIr&& body)
		{
			_body = std::move(body);
		}

		std::ostream& printType(std::ostream& out) const;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return *this; }
		const auto& prototype() const { return _prototype; }
		bool hasBody() const { return !!_body; }
		const auto& body() const { assert(_body); return *_body; }
		const auto& isIntrinsic() const { return _isIntrinsic; }
	};
}

#endif
