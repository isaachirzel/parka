#ifndef WARBLER_AST_TYPE_TYPE_DEFINITION_BODY_HPP
#define WARBLER_AST_TYPE_TYPE_DEFINITION_BODY_HPP

#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	struct TypeDefinitionBody
	{
		virtual ~TypeDefinitionBody() = default;
		virtual bool validate(semantics::Context& context) = 0;
		virtual void print_tree(u32 depth = 0) const = 0;
	};
}

#endif
