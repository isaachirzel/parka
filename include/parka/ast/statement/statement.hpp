#ifndef PARKA_AST_STATEMENT_HPP
#define PARKA_AST_STATEMENT_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/entity/statement_id.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

struct JumpStatement;
struct Declaration;

struct Statement
{
	static Optional<StatementId> parse(Token& token);

	virtual ~Statement() {}
	virtual bool validate(SymbolTable& symbols) = 0;
};

#endif
