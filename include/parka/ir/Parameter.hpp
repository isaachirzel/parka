#ifndef PARKA_IR_PARAMETER_HPP
#define PARKA_IR_PARAMETER_HPP

#include "parka/ir/Entity.hpp"

namespace parka::ir
{
	class ParameterIr : public EntityIr
	{
		String _symbol;
		ValueType _type;

	public:

		ParameterIr(ValueType&& type) :
		_type(std::move(type))
		{}
		ParameterIr(ParameterIr&&) = default;
		ParameterIr(const ParameterIr&) = delete;

		const String& symbol() const { return _symbol; }
		EntityType entityType() const { return EntityType::Parameter; }
		const ValueType *valueType() const { return &_type; }
	};
}

#endif
