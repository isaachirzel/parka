#ifndef WARBLER_AST_POSTFIX_EXPRESSION_H
#define WARBLER_AST_POSTFIX_EXPRESSION_H

// local headers
#include <warbler/ast/expression/primary.h>

typedef enum PostfixType
{
	POSTFIX_NONE,
	POSTFIX_INCREMENT,
	POSTFIX_DECREMENT,
	POSTFIX_ARRAY,
	POSTFIX_FUNCTION,
	POSTFIX_DOT
} PostfixType;

typedef struct PostfixExpression
{
	union
	{
		struct PostfixExpression *postfix;
		PrimaryExpression *primary;
	};
	PostfixType type;
} PostfixExpression;

void postfix_expression_init(PostfixExpression *self);
void postfix_expression_free(PostfixExpression *self);
Error postfix_expression_parse(PostfixExpression *self, TokenIterator *iter);
void postfix_expression_print_tree(PostfixExpression *self, unsigned depth);

#endif
