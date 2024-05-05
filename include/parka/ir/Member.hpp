#ifndef PARKA_IR_MEMBER_HPP
#define PARKA_IR_MEMBER_HPP

#include "parka/ir/Assignable.hpp"
#include "parka/ir/LValue.hpp"
#include "parka/ir/Value.hpp"

namespace parka::ir
{
	class MemberIr: public LValue
	{
		Type _type;

	public:

		MemberIr(Type&& Type):
			LValue(ResolvableType::Member),
			_type(std::move(Type))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const Type& type() const { return _type; }
	};
}

#endif
