#ifndef WARBLER_AST_TYPE_TYPE_HPP
#define WARBLER_AST_TYPE_TYPE_HPP

#include <warbler/ast/identifier.hpp>
#include <warbler/ast/type/type_definition.hpp>

#include <warbler/semantics/context.hpp>
#include <warbler/token.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::ast
{
	struct TypeDefinition
	{
		virtual ~TypeDefinition() {}

		static Result<Ptr<TypeDefinition>> parse(TokenIterator& iter);

		virtual bool validate(semantics::ModuleContext& mod_ctx) = 0;
		virtual void print_tree(u32 depth = 0) const = 0;

		virtual Member *get_member(const String& member_name) = 0;
		virtual bool is_primitive() const = 0;
		virtual const Identifier& name() const = 0;
	};
}

#endif
