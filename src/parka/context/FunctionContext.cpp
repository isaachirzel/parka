#include "parka/context/FunctionContext.hpp"

namespace parka
{
	FunctionContext::FunctionContext(PrototypeContext&& prototype, ExpressionContext& body) :
	_prototype(std::move(prototype)),
	_body(body)
	{}
}
