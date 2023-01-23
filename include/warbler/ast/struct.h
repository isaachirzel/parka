#ifndef WARBLER_AST_STRUCT_H
#define WARBLER_AST_STRUCT_H

#include "warbler/ast/member.h"

typedef struct Struct
{
	Token name;
	char *symbol;
	MemberList members;
} Struct;

void structFree(Struct *node);

#endif
