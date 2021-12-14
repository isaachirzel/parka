#ifndef WARBLER_AST_PRIMARY_EXPRESSION_H
#define WARBLER_AST_PRIMARY_EXPRESSION_H

// local headers
#include <warbler/ast/identifier.h>
#include <warbler/ast/constant.h>

struct Expression;

typedef enum PrimaryType
{
	PRIMARY_IDENTIFIER,
	PRIMARY_CONSTANT,
	PRIMARY_EXPRESSION
} PrimaryType;

typedef struct PrimaryExpression
{
	union
	{
		Identifier *identifier;
		Constant *constant;
		struct Expression *expression;
	};
	PrimaryType type;
} PrimaryExpression;

void primary_expression_init(PrimaryExpression *primary);
void primary_expression_free(PrimaryExpression *primary);
Error primary_expression_parse(PrimaryExpression *primary, TokenIterator *iter);

#endif
