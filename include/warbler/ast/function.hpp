#ifndef WARBLER_AST_FUNCTION_HPP
#define WARBLER_AST_FUNCTION_HPP

// local headers
#include <warbler/ast/typename.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/parameter.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/statement/compound_statement.hpp>
namespace warbler
{
typedef struct Function
{
	Identifier name;
	ParameterList parameters;
	Typename return_type;

	union
	{
		Expression *inline_body;
		CompoundStatement *compound_body;
	};
	
	bool is_inline;
} Function;

void function_init(Function *function);
void function_free(Function *function);
Error function_parse(Function *function, TokenIterator& iter);
}
#endif
