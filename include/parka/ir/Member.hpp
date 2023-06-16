#ifndef PARKA_IR_MEMBER_HPP
#define PARKA_IR_MEMBER_HPP

#include "parka/ir/Entity.hpp"

namespace parka::ir
{
	class MemberIr : public EntityIr
	{
		ValueType _valueType;

	public:

		MemberIr(ValueType&& valueType) :
		_valueType(std::move(valueType))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		EntityType entityType() const { return EntityType::Member; }
		const ValueType *valueType() const { return &_valueType; }
	};
}

#endif
