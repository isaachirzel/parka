#ifndef WARBLER_AST_TYPE_H
#define WARBLER_AST_TYPE_H

#include "warbler/symbol.h"
#include "warbler/token.h"
#include "warbler/util/primitives.h"

// TODO: Add pointer info

struct Expression;

typedef struct Type
{
	usize index;
	SymbolType type;
} Type;

typedef struct TypeAnnotation
{
	Token token;
	Type type;
} TypeAnnotation;

void typeFree(Type *node);
void typeAnnotationFree(TypeAnnotation *node);
/**
 * @return Malloc'd string representation of type
 */
char *typeGetName(const Type *type);
Type typeFromExpression(struct Expression *expression, const Type *expectedType);
Type typeDuplicate(const Type *type);
bool typeCanConvert(const Type *to, const Type *from);

extern const Type voidType;

#endif