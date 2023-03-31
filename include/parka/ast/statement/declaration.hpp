#ifndef PARKA_AST_STATEMENT_DECLARATION_HPP
#define PARKA_AST_STATEMENT_DECLARATION_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/module.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/optional.hpp"

class Declaration : public Statement
{
	EntityId _variableId;
	ExpressionId _value;

	Declaration(EntityId variableId, ExpressionId value) :
	_variableId(variableId),
	_value(value)
	{}

public:

	Declaration(Declaration&&) = default;
	Declaration(const Declaration&) = delete;
	~Declaration() = default;

	static Optional<StatementId> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);

	const auto& variableId() const { return _variableId; }
	const auto& value() const { return _value; }
};

#endif
