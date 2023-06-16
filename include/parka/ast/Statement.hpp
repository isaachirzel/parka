#ifndef PARKA_SYNTAX_STATEMENT_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	enum class StatementType
	{
		Declaration,
		Expression,
		Jump
	};

	struct StatementContext
	{
		virtual ~StatementContext() {}
		virtual StatementType statementType() const = 0;
	};

	struct StatementSyntax
	{
		virtual ~StatementSyntax() {}
		virtual StatementType statementType() const = 0;
		virtual const Snippet& snippet() const = 0;
		virtual StatementContext *validate(SymbolTable& symbolTable) = 0;

		static StatementSyntax *parse(Token& token);
	};

	std::ostream& operator<<(std::ostream& out, const StatementType& type);
}

#endif
