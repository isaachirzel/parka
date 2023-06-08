#ifndef PARKA_SYNTAX_STATEMENT_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_SYNTAX_HPP

#include "parka/enum/StatementType.hpp"
#include "parka/Token.hpp"
#include "parka/repository/StatementSyntaxId.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct StatementSyntax
	{
		virtual ~StatementSyntax() {}
		virtual StatementType statementType() const = 0;

		static const StatementSyntax *parse(Token& token);
		static const StatementSyntax& create(StatementSyntax&& syntax);
		static StatementSyntaxId idFor(const StatementSyntax& syntax); 
	};
}

#endif
