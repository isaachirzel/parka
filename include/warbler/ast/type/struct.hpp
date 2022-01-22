#ifndef WARBLER_AST_TYPE_STRUCT_DEFINITION_HPP
#define WARBLER_AST_TYPE_STRUCT_DEFINITION_HPP

// local headers
#include <warbler/ast/type/member.hpp>

namespace warbler::ast
{
	class Struct
	{
	private:

		Array<Member> _members;

	public:

		Struct(Array<Member>&& members);

		static Result<Struct> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
