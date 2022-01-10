#ifndef WARBLER_AST_$_STATEMENT_HPP
#define WARBLER_AST_$_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>

namespace warbler
{
typedef struct SelectionStatement
{
	ConditionalExpression expr;
} SelectionStatement;

Error selection_statement_statement_parse(SelectionStatement *self, TokenIterator& iter);
void selection_statement_statement_free(SelectionStatement *self);
}
#endif
