#ifndef PARKA_AST_STATEMENT_DECLARATION_HPP
#define PARKA_AST_STATEMENT_DECLARATION_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/optional.hpp"

class Declaration : public Statement
{
	usize _variableId;
	Box<Expression> _value;

	Declaration(usize variableId, Box<Expression>&& value) :
	_variableId(variableId),
	_value(std::move(value))
	{}

public:

	Declaration(Declaration&&) = default;
	Declaration(const Declaration&) = delete;
	~Declaration() = default;

	static Optional<Box<Statement>> parse(Token& token);

	bool validate(SymbolTable& localTable);

	const auto& variableId() const { return _variableId; }
	const auto& value() const { return *_value; }
};

#endif
