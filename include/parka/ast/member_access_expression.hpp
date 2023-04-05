#ifndef PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP
#define PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP

#include "parka/ast/expression.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class MemberAccess : public Expression
{
	ExpressionId _expression;
	Token _member;

	MemberAccess(ExpressionId&& expression, const Token& member) :
	_expression(std::move(expression)),
	_member(member)
	{}

public:

	static Optional<ExpressionId> parse(Token& token, ExpressionId primary);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;

	const auto& expression() const { return _expression; }
	const auto& member() const { return _member; }
};

#endif
