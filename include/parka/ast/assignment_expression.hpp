#ifndef PARKA_AST_EXPRESSION_ASSIGNMENT_HPP
#define PARKA_AST_EXPRESSION_ASSIGNMENT_HPP

#include "parka/ast/expression.hpp"

enum AssignmentType
{
	ASSIGNMENT_BECOME,
	ASSIGNMENT_MULTIPLY,
	ASSIGNMENT_DIVIDE,
	ASSIGNMENT_MODULUS,
	ASSIGNMENT_ADD,
	ASSIGNMENT_SUBTRACT,
	ASSIGNMENT_LEFT_BIT_SHIFT,
	ASSIGNMENT_RIGHT_BIT_SHIFT,
	ASSIGNMENT_BITWISE_AND,
	ASSIGNMENT_BITWISE_OR,
	ASSIGNMENT_BITWISE_XOR
};

class Assignment : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;
	AssignmentType _type;

	Assignment(ExpressionId&& lhs, ExpressionId&& rhs, AssignmentType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	Assignment(Assignment&&) = default;
	Assignment(const Assignment&) = delete;
	~Assignment() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;
	
	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
	const auto& type() const { return _type; }
};

#endif
