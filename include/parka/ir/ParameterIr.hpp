#ifndef PARKA_IR_PARAMETER_HPP
#define PARKA_IR_PARAMETER_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class ParameterIr: public EntityIr
	{
		String _symbol;
		const TypeIr& _type;

	public:

		ParameterIr(const TypeIr& type):
			EntityIr(EntityType::Parameter),
			_type(type)
		{}
		ParameterIr(ParameterIr&&) = default;
		ParameterIr(const ParameterIr&) = delete;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return _type; }
	};
}

#endif
