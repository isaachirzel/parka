#ifndef PARKA_IR_FUNCTION_IR_HPP
#define PARKA_IR_FUNCTION_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class FunctionIr: public EntityIr
	{
		String _symbol;
		PrototypeIr _prototype;
		FunctionBodyIr _body;

	public:

		FunctionIr(String symbol, PrototypeIr&& prototype, FunctionBodyIr&& body);
		FunctionIr(FunctionIr&&) = default;
		FunctionIr(const FunctionIr&) = delete;

		const String& symbol() const { return _symbol; }
		const auto& prototype() const { return _prototype; }
		auto& body() { return _body; }
		const auto& body() const { return _body; }
		const TypeIr& type() const { return InvalidTypeIr::functionType; }

		friend std::ostream& operator<<(std::ostream& out, const FunctionIr& function);
	};
}

#endif
