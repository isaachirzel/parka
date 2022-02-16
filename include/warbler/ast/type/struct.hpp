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

		Array<Member> _members;

	public:

		Struct(Array<Member>&& members);

		static Result<Struct> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
