#ifndef WARBLER_AST_EXPRESSION_POSTFIX_EXRESSION
#define WARBLER_AST_EXPRESSION_POSTFIX_EXRESSION

#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	enum PostfixType
	{
		POSTFIX_NONE,
		POSTFIX_INDEX,
		POSTFIX_FUNCTION_CALL,
		POSTFIX_MEMBER
	};

	class PostfixExpression : public Expression
	{
	private:

		Ptr<Expression> _expression;

		union
		{
			Ptr<Expression> _index;
			Array<Argument> _arguments;
			Name _member;
		};

		PostfixType _type;
		// call parse then check for type
		// not sure how to do this

	public:

		PostfixExpression(Ptr<Expression>&& expression, Ptr<Expression>&& index);
		PostfixExpression(Ptr<Expression>&& expression, Array<Ptr<Expression>>&& arguments);
		PostfixExpression(Ptr<Expression>&& expression, Name&& member);
		

	};
}

#endif
