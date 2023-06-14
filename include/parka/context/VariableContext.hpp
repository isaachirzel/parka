#ifndef PARKA_CONTEXT_VARIABLE_CONTEXT_HPP
#define PARKA_CONTEXT_VARIABLE_CONTEXT_HPP

#include "parka/repository/EntityContext.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
{
	class VariableContext: public EntityContext
	{
		ValueType _type;
	
	public:

		VariableContext(ValueType&& type);
		VariableContext(VariableContext&&) = default;
		VariableContext(const VariableContext&) = delete;

		const auto& type() const { return _type; }
	};
}

#endif
