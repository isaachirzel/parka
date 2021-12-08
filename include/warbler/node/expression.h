#ifndef WARBLER_NODE_EXPRESSION_H
#define WARBLER_NODE_EXPRESSION_H

typedef struct Expression
{
	String string;
} Expression;

extern Error expression_parse(Expression **out, const Token *token);

#endif
