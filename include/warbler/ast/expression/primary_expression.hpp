#ifndef WARBLER_AST_PRIMARY_EXPRESSION_HPP
#define WARBLER_AST_PRIMARY_EXPRESSION_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/expression/constant.hpp>
#include <warbler/ast/expression/prefix.hpp>
#include <warbler/ast/expression/postfix.hpp>
namespace warbler
{
struct Expression;

typedef enum PrimaryType
{
	PRIMARY_IDENTIFIER,
	PRIMARY_CONSTANT,
	PRIMARY_EXPRESSION
} PrimaryType;

typedef struct PrimaryExpression
{
	PrefixList prefixes;
	PostfixList postfixes;

	union
	{
		Identifier identifier;
		Constant constant;
		struct Expression *expression;
	};
	PrimaryType type;
} PrimaryExpression;

void primary_expression_init(PrimaryExpression *self);
void primary_expression_free(PrimaryExpression *self);
Error primary_expression_parse(PrimaryExpression *self, TokenIterator& iter);
void primary_expression_print_tree(PrimaryExpression *self, unsigned depth);
}
#endif
