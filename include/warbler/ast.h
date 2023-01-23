#ifndef WARBLER_AST_H
#define WARBLER_AST_H

#include "warbler/ast/expression.h"
#include "warbler/ast/type.h"
#include "warbler/symbol_id.h"

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

typedef struct Struct
{
	Token name;
	char *symbol;
	MemberList members;
} Struct;

typedef struct Module
{
	char *symbol;
	IdList functionIds;
	IdList structIds;
} Module;

typedef struct Package
{
	char *symbol;
	Module *modules;
	usize moduleCount;
} Package;

void argumentListFree(ArgumentList *node);
void memberFree(Member *node);
void memberListFree(MemberList *node);
void structFree(Struct *node);

void moduleFree(Module *node);
void packageFree(Package *node);

#endif
