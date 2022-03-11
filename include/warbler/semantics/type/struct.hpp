#ifndef WARBLER_SEMANTICS_STRUCT_HPP
#define WARBLER_SEMANTICS_STRUCT_HPP

#include <warbler/semantics/type/member.hpp>
#include <warbler/util/table.hpp>

namespace warbler::semantics
{
	class Struct
	{
		Table<Member> _members;

	public:

		Struct(Table<Member>&& members);
	};
}

#endif