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
		Type _type;
		bool _is_public;

	public:

		Member(Identifier&& id, Type&& type, bool is_public);

		static Result<Member> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx);
		void print_tree(u32 depth = 0) const;

		const Identifier& name() const { return _name; }
		const Type& type() const { return _type; }
	};
}

#endif
