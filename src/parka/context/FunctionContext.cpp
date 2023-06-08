#include "parka/context/FunctionContext.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	const FunctionContext *FunctionContext::validate(FunctionSymbolTable& symbolTable)
	{
		// bool success = true;
		// const auto& syntax = symbolTable.syntaxId().getFunction();

		// auto prototype = PrototypeContext::validate(syntax.prototype(), symbolTable);
		// auto body = ExpressionContext::validate(syntax.body(), symbolTable);

		// if (!prototype)
		// 	success = false;
		// if (prototype)


		log::notImplemented(here());
	}
}
