#ifndef WARBLER_SEMANTICS_MEMBER_HPP
#define WARBLER_SEMANTICS_MEMBER_HPP

#include <warbler/semantics/type/type.hpp>

namespace warbler::semantics
{
	class Member
	{
		Type _type;
		bool _is_public;

	public:

		Member(Type&& type, bool is_public);
	};
}

#endif