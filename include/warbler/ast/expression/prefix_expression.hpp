#ifndef WARBLER_AST_EXPRESSION_PREFIX_EXRESSION
#define WARBLER_AST_EXPRESSION_PREFIX_EXRESSION

#include <warbler/ast/expression/postfix_expression.hpp>

namespace warbler::ast
{
	enum PrefixType
	{
		PREFIX_NONE,
		PREFIX_REFERENCE,
		PREFIX_DEREFERENCE,
		PREFIX_POSITIVE,
		PREFIX_NEGATIVE,
		PREFIX_BITWISE_NOT,
		PREFIX_BOOLEAN_NOT
	};

	class PrefixExpression : public Expression
	{
	private:

		Ptr<Expression> _expression;
		PrefixType _type;

	public:

		PrefixExpression(Ptr<Expression>&& expression, PrefixType type);

	};
}

#endif