#ifndef PARKA_IR_MEMBER_HPP
#define PARKA_IR_MEMBER_HPP

#include "parka/ir/AssignableIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/ValueIr.hpp"

namespace parka::ir
{
	class MemberIr: public LValueIr
	{
		TypeIr _type;

	public:

		MemberIr(TypeIr&& TypeIr):
			LValueIr(ResolvableType::Member),
			_type(std::move(TypeIr))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const TypeIr& type() const { return _type; }
	};
}

#endif
