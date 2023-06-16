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
		virtual ~StatementAst() {}
		virtual StatementType statementType() const = 0;
		virtual const Snippet& snippet() const = 0;
		virtual ir::StatementIr *validate(SymbolTable& symbolTable) = 0;

		static StatementAst *parse(Token& token);
	};

	std::ostream& operator<<(std::ostream& out, const StatementType& type);
}

#endif
