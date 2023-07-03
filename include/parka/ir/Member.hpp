#ifndef PARKA_IR_MEMBER_HPP
#define PARKA_IR_MEMBER_HPP

#include "parka/symbol/Resolution.hpp"
#include "parka/ir/Value.hpp"

namespace parka::ir
{
	class MemberIr: public Resolution, public Value
	{
		Type _type;

	public:

		MemberIr(Type&& Type):
		Resolution(ResolvableType::Member),
		_type(std::move(Type))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const Type& valueType() const { return _type; }
	};
}

#endif
