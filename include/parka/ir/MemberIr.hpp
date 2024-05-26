#ifndef PARKA_IR_MEMBER_IR_HPP
#define PARKA_IR_MEMBER_IR_HPP

#include "parka/ir/LValueIr.hpp"

namespace parka::ir
{
	class MemberIr: public LValueIr
	{
		const TypeIr& _type;

	public:

		MemberIr(TypeIr& TypeIr):
			LValueIr(ResolvableType::Member),
			_type(TypeIr)
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const TypeIr& type() const { return _type; }
	};
}

#endif
