#ifndef WARBLER_AST_TYPE_TYPE_DEFINITION
#define WARBLER_AST_TYPE_TYPE_DEFINITION

#include <warbler/semantics/context.hpp>
#include <warbler/token.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::ast
{
	struct TypeDefinition
	{
		virtual ~TypeDefinition() = default;
		virtual bool validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx) = 0;
		virtual void print_tree(u32 depth = 0) const = 0;

		static Result<Ptr<TypeDefinition>> parse(TokenIterator& iter);
	};
}

#endif
