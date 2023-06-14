#include "parka/context/VariableContext.hpp"

namespace parka
{
	VariableContext::VariableContext(ValueType&& type) :
	_type(std::move(type))
	{}
}
