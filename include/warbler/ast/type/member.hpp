#ifndef WARBLER_AST_TYPE_MEMBER_HPP
#define WARBLER_AST_TYPE_MEMBER_HPP

// local headers
#include <warbler/ast/name.hpp>
#include <warbler/ast/typename.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Member
	{
	private:

		Name _name;
		Typename _type;
		bool _is_public;

	public:

		Member(Name&& id, Typename&& type, bool is_public);

		static Result<Member> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx);
		void print_tree(u32 depth = 0) const;

		const Name& name() const { return _name; }
		const Typename& type() const { return _type; }
	};
}

#endif
