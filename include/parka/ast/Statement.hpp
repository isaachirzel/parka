#ifndef PARKA_AST_STATEMENT_HPP
#define PARKA_AST_STATEMENT_HPP

#include "parka/ir/Statement.hpp"
#include "parka/parser/Token.hpp"
#include "parka/enum/StatementType.hpp"
#include "parka/symbol/SymbolTable.hpp"

namespace parka::ast
{
	struct StatementAst
	{
		const StatementType statementType;

	public:

		StatementAst(StatementType statementType) :
		statementType(statementType)
		{}
		virtual ~StatementAst() {}

		virtual const Snippet& snippet() const = 0;
	};
}

#endif
