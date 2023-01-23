#ifndef WARBLER_AST_MEMBER_H
#define WARBLER_AST_MEMBER_H

#include "warbler/ast/type.h"
#include "warbler/token.h"

typedef struct Member
{
	Token name;
	char *symbol;
	TypeAnnotation annotation;
	bool isPublic;
	usize readCount;
	usize writeCount;
} Member;

typedef struct MemberList
{
	Member *data;
	usize count;
} MemberList;

void memberFree(Member *node);
void memberListFree(MemberList *node);

#endif
