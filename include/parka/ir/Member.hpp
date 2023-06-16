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
		EntityIr(EntityType::Member),
		_valueType(std::move(valueType))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const ValueType *valueType() const { return &_valueType; }
	};
}

#endif
