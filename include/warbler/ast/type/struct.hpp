#ifndef WARBLER_AST_TYPE_STRUCT_DEFINITION_HPP
#define WARBLER_AST_TYPE_STRUCT_DEFINITION_HPP

// local headers
#include <warbler/ast/type/member.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/ast/type/type_definition_body.hpp>

namespace warbler::ast
{
	class Struct : public TypeDefinitionBody
	{
	private:

		Array<Member> _members;

	public:

		Struct(Array<Member>&& members);
		~Struct() = default;

		static Result<Struct> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
