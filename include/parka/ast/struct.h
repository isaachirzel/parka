#ifndef PARKA_AST_STRUCT_H
#define PARKA_AST_STRUCT_H

#include "parka/ast/member.h"

typedef struct Struct
{
	Token name;
	char *symbol;
	MemberList members;
} Struct;

bool parseStruct(usize *out, Token *token, const char *package);
bool validateStruct(Struct *node, const Scope *packageScope);
void structFree(Struct *node);

#endif
