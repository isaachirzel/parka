#ifndef WARBLER_AST_DECLARATION_STATEMENT_HPP
#define WARBLER_AST_DECLARATION_STATEMENT_HPP

// local headers
#include <warbler/ast/typename.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/expression/expression.hpp>
namespace warbler
{
typedef struct DeclarationStatement
{
	Typename *type;
	Identifier *identifier;
	Expression *expression;
} DeclarationStatement;

Error declaration_statement_parse(DeclarationStatement *declaration, TokenIterator& iter);
void declaration_statement_free(DeclarationStatement *declaration);
}
#endif
