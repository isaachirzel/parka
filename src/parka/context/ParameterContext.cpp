#include "parka/context/ParameterContext.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	ParameterContext::ParameterContext(ValueType&& type, bool isMutable) :
	_type(std::move(type)),
	_isMutable(isMutable)
	{}

	ParameterContext *ParameterContext::validate(const ParameterSyntax& syntax, FunctionSymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
