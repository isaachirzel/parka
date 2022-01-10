#ifndef WARBLER_AST_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_HPP

#include <warbler/ast/statement/expression_statement.hpp>
#include <warbler/ast/statement/declaration_statement.hpp>
#include <warbler/ast/statement/compound_statement.hpp>
#include <warbler/ast/statement/selection_statement.hpp>
#include <warbler/ast/statement/loop_statement.hpp>
#include <warbler/ast/statement/jump_statement.hpp>
namespace warbler
{
typedef enum StatementType
{
	STATEMENT_EXPRESSION,
	STATEMENT_DECLARATION,
	STATEMENT_COMPOUND,
	STATEMENT_SELECTION,
	STATEMENT_LOOP,
	STATEMENT_JUMP
} StatementType;

typedef struct Statement
{

	union
	{
		ExpressionStatement expression;
		DeclarationStatement declaration;
		CompoundStatement compound;
		//SelectionStatment selection;
		LoopStatement loop;
		JumpStatement jump;
	};
	StatementType type;
} Statement;

void statement_init(Statement *self);
void statement_parse(Statement *self, TokenIterator& iter);
void statement_print_tree(Statement *self);
}
#endif
