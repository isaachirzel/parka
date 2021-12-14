#ifndef WARBLER_AST_POSTFIX_EXPRESSION_H
#define WARBLER_AST_POSTFIX_EXPRESSION_H

// local headers
#include <warbler/ast/expression/primary.h>

typedef enum PostfixType
{
	POSTFIX_INCREMENT,
	POSTFIX_DECREMENT,
	POSTFIX_ARRAY,
	POSTFIX_FUNCTION,
	POSTFIX_DOT
} PostfixType;

typedef struct PostfixExpression
{
	PostfixType type;
	union
	{
		struct PostfixExpression *postifx;
		PrimaryExpression *primary;
	};
} PostfixExpression;

#endif
