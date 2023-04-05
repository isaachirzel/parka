#ifndef PARKA_AST_EXPRESSION_CALL_HPP
#define PARKA_AST_EXPRESSION_CALL_HPP

#include "parka/ast/expression.hpp"

class CallExpression : public Expression
{
	ExpressionId _primary;
	Array<ExpressionId> _arguments;

	CallExpression(ExpressionId&& primary, Array<ExpressionId>&& arguments) :
	_primary(std::move(primary)),
	_arguments(std::move(arguments))
	{}

public:

	CallExpression(CallExpression&&) = default;
	CallExpression(const CallExpression&) = delete;
	~CallExpression() = default;

	static Optional<ExpressionId> parse(Token& token, ExpressionId primary);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;

	const auto& arguments() const { return _arguments; }
};

#endif
