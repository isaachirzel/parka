#ifndef WARBLER_AST_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_HPP

#include <warbler/ast/typename.hpp>
#include <warbler/token.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::ast
{
	struct Expression
	{
		virtual ~Expression() = default;
		virtual bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx) = 0;
		virtual Typename* get_type(semantics::ModuleContext& mod_ctx) const = 0;
		virtual void print_tree(u32 depth = 0) const = 0;
		virtual const Location& location() const = 0;

		static Result<Ptr<Expression>> parse(TokenIterator& iter);
	};
}

#endif
