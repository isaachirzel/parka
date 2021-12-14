#ifndef WARBLER_AST_EXPRESSION_PREFIX_H
#define WARBLER_AST_EXPRESSION_PREFIX_H

// local headers
#include <warbler/ast/expression/postfix.h>

typedef enum
{
	PREFIX_NONE,
	PREFIX_INCREMENT,
	PREFIX_DECREMENT,
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE
} PrefixType;

typedef struct
{
	// TODO make these have prefix operators intead of prefix type
	PrefixType type;
	union
	{
		PostfixExpression *postfix;
	};
} PrefixExpression;

Error prefix_expression_parse(PrefixExpression *out, TokenIterator *iter);
void prefix_expression_free(PrefixExpression *prefix);

#endif
