#ifndef WARBLER_AST_JUMP_STATEMENT_HPP
#define WARBLER_AST_JUMP_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/expression/expression.hpp>
namespace warbler
{
typedef enum JumpType
{
	JUMP_CONTINUE,
	JUMP_BREAK,
	JUMP_RETURN,
	JUMP_EMIT
} JumpType;

typedef struct JumpStatement
{
	JumpType type;
	Expression *value;
} JumpStatement;

Error jump_statement_parse(JumpStatement *jump, TokenIterator& iter);
void jump_statement_free(JumpStatement *jump);
}
#endif
