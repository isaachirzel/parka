#ifndef PARKA_AST_STATEMENT_HPP
#define PARKA_AST_STATEMENT_HPP

#include "parka/symbol/statement_id.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

struct Statement
{
	static Optional<StatementId> parse(Token& token);

	virtual ~Statement() {}
	virtual bool validate(LocalSymbolTable& symbols) = 0;
};

#endif
