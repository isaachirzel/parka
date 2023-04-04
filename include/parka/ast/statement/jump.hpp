#ifndef PARKA_AST_STATEMENT_JUMP_HPP
#define PARKA_AST_STATEMENT_JUMP_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"

#include "parka/token.hpp"
#include "parka/util/optional.hpp"

enum class JumpType
{
	Continue,
	Break,
	Return,
	Yield
};

class JumpStatement : public Statement
{
	Token _token;
	Optional<ExpressionId> _value;
	JumpType _type;

	JumpStatement(const Token& token, JumpType type, Optional<ExpressionId>&& value) :
	_token(token),
	_value(std::move(value)),
	_type(type)
	{}

public:

	JumpStatement(JumpStatement&&) = default;
	JumpStatement(const JumpStatement&) = delete;
	~JumpStatement() = default;

	static Optional<StatementId> parse(Token& token);

	bool validate(const EntityId& functionId);

	const auto& token() const { return _token; }
	bool hasValue() const { return _value; }
	const auto& value() const { return _value; }
	const auto& type() const { return _type; }
};

#endif
