#ifndef PARKA_IR_MEMBER_HPP
#define PARKA_IR_MEMBER_HPP

#include "parka/symbol/Resolution.hpp"

namespace parka::ir
{
	class MemberIr: public Resolution
	{
		ValueType _valueType;

	public:

		MemberIr(ValueType&& valueType):
		Resolution(ResolvableType::Member),
		_valueType(std::move(valueType))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const ValueType *valueType() const { return &_valueType; }
	};
}

#endif
