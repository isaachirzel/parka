#include "parka/context/FunctionContext.hpp"
#include "parka/context/ExpressionContext.hpp"
#include "parka/context/PrototypeContext.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	const FunctionContext *FunctionContext::validate(FunctionSymbolTable& symbolTable)
	{
		const auto& syntax = symbolTable.syntax();

		auto prototype = PrototypeContext::validate(syntax.prototype(), symbolTable);
		auto body = ExpressionContext::validate(syntax.body(), symbolTable);

		if (!prototype || !body)
			return {};

		log::notImplemented(here());
	}
}
