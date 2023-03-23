#ifndef PARKA_AST_STATEMENT_HPP
#define PARKA_AST_STATEMENT_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/optional.hpp"

struct JumpStatement;
struct Declaration;

struct Statement
{
	static Optional<Box<Statement>> parse(Token& token);

	virtual ~Statement() {}
	virtual bool validate(SymbolTable& localTable) = 0;
};

#endif
