#ifndef PARKA_AST_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_HPP

#include "parka/node/expression_id.hpp"
#include "parka/token.hpp"
#include "parka/type/type.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/ref.hpp"

struct Expression
{
	static Optional<ExpressionId> parse(Token& token);

	virtual ~Expression() {}

	virtual bool validate(const EntityId& functionId) = 0;
	virtual Optional<Type> getType() const = 0;
};

#endif
