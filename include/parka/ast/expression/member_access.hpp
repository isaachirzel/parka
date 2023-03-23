#ifndef PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP
#define PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class MemberAccess : public Expression
{
	Box<Expression> _expression;
	Token _member;

	MemberAccess(Box<Expression>&& expression, const Token& member) :
	_expression(std::move(expression)),
	_member(member)
	{}

public:

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& expression() const { return *_expression; }
	const auto& member() const { return _member; }
};

#endif
