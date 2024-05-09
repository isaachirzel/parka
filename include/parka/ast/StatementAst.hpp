#ifndef PARKA_AST_STATEMENT_AST_HPP
#define PARKA_AST_STATEMENT_AST_HPP

#include "parka/enum/StatementType.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	struct StatementAst
	{
		const StatementType statementType;

	public:

		StatementAst(StatementType statementType):
		statementType(statementType)
		{}
		virtual ~StatementAst() {}

		virtual const Snippet& snippet() const = 0;
	};
}

#endif
