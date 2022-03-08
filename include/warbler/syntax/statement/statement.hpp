#ifndef WARBLER_SYNTAX_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_HPP

#include <warbler/util/result.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	struct Statement
	{
		virtual ~Statement() = default;

		static Result<Ptr<Statement>> parse(lexicon::Token& token);
	};
}

#endif
