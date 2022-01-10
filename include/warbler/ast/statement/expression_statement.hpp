#ifndef WARBLER_AST_EXPRESSION_STATEMENT_HPP
#define WARBLER_AST_EXPRESSION_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
namespace warbler
{
typedef struct ExpressionStatement
{
	
} ExpressionStatement;

Error Expression_statement_parse(ExpressionStatement *Expression, TokenIterator& iter);
void Expression_statement_free(ExpressionStatement *Expression);
}
#endif
