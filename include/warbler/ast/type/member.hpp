#ifndef WARBLER_AST_TYPE_MEMBER_HPP
#define WARBLER_AST_TYPE_MEMBER_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/typename.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Member
	{
	private:

		Identifier _name;
		Typename _type;
		bool _is_public;

	public:

		Member(Identifier&& name, Typename&& type, bool is_public);

		static Result<Member> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
