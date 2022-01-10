#ifndef WARBLER_AST_LOOP_STATEMENT_HPP
#define WARBLER_AST_LOOP_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/loop_condition.hpp>
#include <warbler/ast/statement/statement.hpp>
namespace warbler
{
typedef enum LoopType
{
	LOOP_FOR,
	LOOP_WHILE,
	LOOP_LOOP
} LoopType;

typedef struct LoopStatement
{
	LoopType type;
	LoopCondition *condition;
	Statement *statement;
} LoopStatement;

Error loop_statement_parse(LoopStatement *loop, TokenIterator& iter);
void loop_statement_free(LoopStatement *loop);
}
#endif
