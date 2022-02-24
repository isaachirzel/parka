#ifndef WARBLER_SYNTAX_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_HPP

#include <warbler/syntax//type.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::syntax
{
	struct Expression
	{
		virtual ~Expression() = default;
		virtual bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx) = 0;
		virtual Type* get_type() = 0;
		virtual void print_tree(u32 depth = 0) const = 0;
		virtual const source::Location& location() const = 0;

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);
	};
}

#endif
