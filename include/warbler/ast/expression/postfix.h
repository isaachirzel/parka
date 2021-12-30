#ifndef WARBLER_AST_POSTFIX_EXPRESSION_H
#define WARBLER_AST_POSTFIX_EXPRESSION_H

// local headers
#include <warbler/ast/parameter.h>

struct Expression;

typedef enum PostfixType
{
	POSTFIX_INDEX,
	POSTFIX_CALL,
	POSTFIX_MEMBER
} PostfixType;

typedef struct Postfix
{
	union
	{
		struct Expression *expression;
		ParameterList parameters;
		Identifier identifier;
	};
	PostfixType type;
} Postfix;

void postfix_init(Postfix *self);
void postfix_free(Postfix *self);
Error postfix_parse(Postfix *self, TokenIterator *iter);
void postfix_print_tree(Postfix *self, unsigned depth);

#endif
