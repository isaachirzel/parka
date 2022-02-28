#ifndef WARBLER_SYNTAX_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_HPP

#include <warbler/semantics/context.hpp>
#include <warbler/util/result.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	struct Statement
	{
		virtual ~Statement() = default;
		virtual void print_tree(u32 depth = 0) const = 0;

		static Result<Ptr<Statement>> parse(lexicon::TokenIterator& iter);
	};
}

#endif
