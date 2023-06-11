#ifndef PARKA_CONTEXT_PARAMETER_CONTEXT_HPP	
#define PARKA_CONTEXT_PARAMETER_CONTEXT_HPP	

#include "parka/repository/EntityContext.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
{
	class ParameterContext : public EntityContext
	{
		ValueType _type;
		bool _isMutable;

	private:

		ParameterContext(ValueType&& type, bool isMutable) :
		_type(std::move(type)),
		_isMutable(isMutable)
		{}
		ParameterContext(ParameterContext&&) = default;
		ParameterContext(const ParameterContext&) = delete;

		EntityType entityType() const { return EntityType::Parameter; }
		const auto& type() const { return _type; }
		const auto& isMutable() const { return _isMutable; }
	};
}

#endif
