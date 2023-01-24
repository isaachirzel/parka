#ifndef WARBLER_AST_EXRPESSION_BLOCK_H
#define WARBLER_AST_EXRPESSION_BLOCK_H

#include "warbler/ast/expression/expression.h"
#include "warbler/ast/type.h"
#include "warbler/util/primitives.h"

struct Statement;

typedef struct Block
{
	struct Statement* statements;
	usize count;
	Type returnType;
	bool hasReturnType;
} Block;

bool parseBlock(Expression *out, Token *token);
bool validateBlock(Block *node, LocalSymbolTable *localTable);
void blockFree(Block *node);
bool blockGetType(Type *out, Block *block, const Type *expected);

#endif
