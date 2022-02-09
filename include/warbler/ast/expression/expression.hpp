#ifndef WARBLER_AST_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_HPP

#include <warbler/token.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::ast
{
	struct Expression
	{
		virtual ~Expression()  = default;
		virtual bool validate(semantics::Context& context) = 0;
		virtual void print_tree(u32 depth = 0) const = 0;

		static Result<Ptr<Expression>> parse(TokenIterator& iter);
	};
}

#endif
