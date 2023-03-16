#ifndef PARKA_AST_MEMBER_H
#define PARKA_AST_MEMBER_H

#include "parka/ast/type.h"
#include "parka/scope.h"
#include "parka/token.h"

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

bool parseMember(Member *out, Token *token);
bool parseMemberList(MemberList *out, Token *token);
bool validateMemberList(MemberList *node, const Scope *packageScope);
void memberFree(Member *node);
void memberListFree(MemberList *node);

#endif
