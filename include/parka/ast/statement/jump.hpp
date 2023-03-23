#ifndef PARKA_AST_STATEMENT_JUMP_HPP
#define PARKA_AST_STATEMENT_JUMP_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/symbol_table.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

typedef enum JumpType
{
	JUMP_CONTINUE,
	JUMP_BREAK,
	JUMP_RETURN,
	JUMP_YIELD
} JumpType;

class JumpStatement : public Statement
{
	Token _token;
	Optional<Box<Expression>> _value;
	JumpType _type;

	JumpStatement(const Token& token, JumpType type, Optional<Box<Expression>>&& value = {}) :
	_token(token),
	_value(std::move(value)),
	_type(type)
	{}

public:

	JumpStatement(JumpStatement&&) = default;
	JumpStatement(const JumpStatement&) = delete;
	~JumpStatement() = default;

	static Optional<Box<Statement>> parse(Token& token);

	bool validate(SymbolTable& localTable);

	const auto& token() const { return _token; }
	bool hasValue() const { return _value; }
	const auto& value() const { return _value; }
	const auto& type() const { return _type; }
};

#endif
