#ifndef PARKA_AST_STATEMENT_HPP
#define PARKA_AST_STATEMENT_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/statement_id.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

struct Statement
{
	static Optional<StatementId> parse(Token& token);

	virtual ~Statement() {}
	virtual bool validate(const EntityId& functionId) = 0;
};

#endif
