#ifndef WARBLER_CONTEXT_H
#define WARBLER_CONTEXT_H

#include <warbler/type.h>
#include <warbler/state.h>
#include <warbler/util/string.h>
#include <warbler/util/primitives.h>
#include <warbler/util/table.h>
#include <warbler/util/array.h>

#include <assert.h>

// Forward declarations
struct AssignmentContext;
struct ConditionalExpressionContext;
struct BooleanOrExpressionContext;
struct BooleanAndExpressionContext;
struct BitwiseOrExpressionContext;
struct BitwiseXorExpressionContext;
struct BitwiseAndExpressionContext;
struct EqualityExpressionContext;
struct RelationalExpressionContext;
struct BitShiftExpressionContext;
struct AdditiveExpressionContext;
struct MultiplicativeExpressionContext;
struct PrefixExpressionContext;
struct PostfixExpressionContext;
struct ConstantContext;
struct VariableContext;
struct ParameterContext;
struct FunctionContext;
struct TypeContext;
struct BlockStatementContext;
struct DeclarationContext;
struct ProgramContext;
struct BlockStatementContext;
struct DeclarationContext;

enum PrimitiveIndex
{
	VOID_INDEX,
	U8_INDEX,
	U16_INDEX,
	U32_INDEX,
	U64_INDEX,
	I8_INDEX,
	I16_INDEX,
	I32_INDEX,
	I64_INDEX,
	F32_INDEX,
	F64_INDEX,
	BOOL_INDEX,
	CHAR_INDEX,
	STRING_INDEX
};

typedef struct SymbolContext
{
	usize index;
	SymbolType type;
} SymbolContext;

typedef struct ConstantContext
{
	union
	{
		char character;
		char *string;
		u64 integer;
		double floating;
		bool boolean;
	};
	ConstantType type;
} ConstantContext;

typedef struct TypeContext
{
	union
	{
		usize index;
		ConstantContext constant;
	};
	AnnotationType type;
} TypeContext;

typedef struct ExpressionContext
{
	union
	{
		ConstantContext *constant;
		SymbolContext *symbol;
		struct AssignmentContext *assignment;
	};
	ExpressionType type;
} ExpressionContext;

typedef struct AssignmentContext
{
	ExpressionContext lhs;
	ExpressionContext rhs;
	AssignmentType type;
} AssignmentContext;

typedef struct MemberContext
{
	char *name;
	TypeContext type;
	bool isPublic;
} MemberContext;

typedef struct StructContext
{
	char *symbol;
	MemberContext *members;
	usize memberCount;
} StructContext;

typedef struct PrimitiveContenxt
{
	const char *symbol;
	PrimitiveType type;
	u32 size;
} PrimitiveContext;

typedef struct VariableContext
{
	char *name;
	TypeContext type;
	bool isExplicitlyTyped;
	bool isMutable;
} VariableContext;

typedef struct StatementContext
{
	union
	{
		ExpressionContext *expression;
		struct BlockStatementContext *block;
		struct DeclarationContext *declaration;
	};

	StatementType type;
} StatementContext;

typedef struct DeclarationContext
{
	usize variableIndex;
	ExpressionContext value;
} DeclarationContext;

typedef struct BlockStatementContext
{
	StatementContext *statements;
	usize count;
} BlockStatementContext;

typedef struct ParameterListContext
{
	usize *data;
	usize count;
} ParameterListContext;

typedef struct FunctionSignatureContext
{
	ParameterListContext parameter;
	TypeContext returnType;
	bool hasReturnType;
} FunctionSignatureContext;

typedef struct ParameterContext
{
	char *name;
	TypeContext type;
	bool isMutable;
} ParameterContext;

typedef struct FunctionContext
{
	char *symbol;
	FunctionSignatureContext signature;
	BlockStatementContext body;
	ParameterContext *parameters;
	usize parameterCount;
	VariableContext *variables;
	usize variableCount;
} FunctionContext;

typedef struct PackageContext
{
	char *name;
} PackageContext;

typedef struct ProgramContext
{
	StructContext* structs;
	usize structCount;
	FunctionContext* functions;
	usize functionCount;
	VariableContext *variables;
	usize variableCount;
	ParameterContext *parameters;
	usize parameterCount;
	PackageContext *packages;
	usize packageCount;
} ProgramContext;

const char *typeAnnotationSymbol(const TypeContext *type, const ProgramContext *program);

extern const PrimitiveContext primitives[];
extern const usize primitiveCount;

void freeBlockStatementContext(BlockStatementContext *context);
void freeDeclarationContext(DeclarationContext *context);
void freeVariableContext(VariableContext *context);
void freeAssignmentContext(AssignmentContext *context);
void freeFunctionSignatureContext(FunctionSignatureContext *context);
void freeMemberContext(MemberContext *member);

#endif
