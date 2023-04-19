#ifndef PARKA_SYNTAX_STATEMENT_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_SYNTAX_HPP

#include "parka/repository/StatementSyntaxId.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct StatementSyntax
	{
		static Optional<StatementSyntaxId> parse(Token& token);

		virtual ~StatementSyntax() {}
	};
}

#endif
