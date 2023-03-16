#ifndef PARKA_AST_TYPE_H
#define PARKA_AST_TYPE_H

#include "parka/scope.h"
#include "parka/symbol.h"
#include "parka/token.h"
#include "parka/util/primitives.h"

// TODO: Add pointer info

struct Expression;

typedef struct Type
{
	usize index;
	SymbolType type;
	
	// Add Literal for better type inference?
	// Literal literal;
	// bool isLiteral;
} Type;

typedef struct TypeAnnotation
{
	Token token;
	Type type;
} TypeAnnotation;

void typeFree(Type *node);
bool parseTypeAnnotation(TypeAnnotation *out, Token *token);
bool validateTypeAnnotation(TypeAnnotation *node, const Scope *packageScope);
void typeAnnotationFree(TypeAnnotation *node);
/**
 * @return Malloc'd string representation of type
 */
char *typeGetName(const Type *type);
Type typeDuplicate(const Type *type);
bool typeCanConvert(const Type *to, const Type *from);

extern const Type voidType;
extern const Type i32Type;

#endif