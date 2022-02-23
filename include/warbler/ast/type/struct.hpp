#ifndef WARBLER_AST_TYPE_STRUCT_HPP
#define WARBLER_AST_TYPE_STRUCT_HPP

// local headers
#include <warbler/ast/type/member.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/ast/type/type_definition.hpp>

namespace warbler::ast
{
	class Struct : public TypeDefinition
	{
	private:

		Identifier _name;
		Array<Member> _members;
		semantics::TypeContext _context;

	public:

		Struct(Identifier&& name, Array<Member>&& members);

		static Result<Struct> parse(TokenIterator& iter, Identifier&& name);

		bool validate(semantics::ModuleContext& mod_ctx);
		void print_tree(u32 depth = 0) const;

		Member *get_member(const String& member_name) { return _context.get_member(member_name); }
		bool is_primitive() const { return false; }
		const Identifier& name() const { return _name; }
	};
}

#endif