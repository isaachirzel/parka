#ifndef PARKA_IR_MEMBER_HPP
#define PARKA_IR_MEMBER_HPP

#include "parka/ir/AssignableIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/ValueIr.hpp"

namespace parka::ir
{
	class MemberIr: public LValueIr
	{
		Type _type;

	public:

		MemberIr(Type&& Type):
			LValueIr(ResolvableType::Member),
			_type(std::move(Type))
		{}
		MemberIr(MemberIr&&) = default;
		MemberIr(const MemberIr&) = delete;

		const Type& type() const { return _type; }
	};
}

#endif
