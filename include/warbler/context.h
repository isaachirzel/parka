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
struct BlockContext;
struct DeclarationContext;
struct ProgramContext;
struct BlockContext;
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

typedef struct SymbolId
{
	SymbolType type;
	u32 package;
	u32 module;
	u32 global;
	u32 local;
} SymbolId;

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
		SymbolId id;
		ConstantContext constant;
	};
	AnnotationType type;
} TypeContext;

typedef struct ExpressionContext
{
	union
	{
		ConstantContext *constant;
		SymbolId *symbolId;
		struct AssignmentContext *assignment;
		struct BlockContext *block;
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
		struct DeclarationContext *declaration;
	};

	bool isDeclaration;
} StatementContext;

typedef struct DeclarationContext
{
	usize variableIndex;
	ExpressionContext value;
} DeclarationContext;

typedef struct BlockContext
{
	StatementContext *statements;
	usize count;
} BlockContext;

typedef struct ParameterListContext
{
	usize *data;
	usize count;
} ParameterListContext;

typedef struct ParameterContext
{
	char *name;
	TypeContext type;
	bool isMutable;
} ParameterContext;

typedef struct FunctionContext
{
	char *symbol;
	TypeContext returnType;
	ExpressionContext body;
	ParameterContext *parameters;
	usize parameterCount;
	VariableContext *variables;
	usize variableCount;
} FunctionContext;

typedef struct ModuleContext
{
	StructContext *structs;
	usize structCount;
	FunctionContext* functions;
	usize functionCount;
} ModuleContext;

typedef struct PackageContext
{
	char *symbol;
	ModuleContext *modules;
	usize moduleCount;
} PackageContext;

typedef struct ProgramContext
{
	PackageContext *packages;
	usize packageCount;
} ProgramContext;

extern const PrimitiveContext primitives[];
extern const usize primitiveCount;

void freeConstantContext(ConstantContext *context);
void freeTypeContext(TypeContext *context);
void freeBlockContext(BlockContext *context);
void freeStructContext(StructContext *context);
void freeDeclarationContext(DeclarationContext *context);
void freeParameterContext(ParameterContext *context);
void freeVariableContext(VariableContext *context);
void freeExpressionContext(ExpressionContext *context);
void freeAssignmentContext(AssignmentContext *context);
void freeFunctionContext(FunctionContext *context);
void freeMemberContext(MemberContext *context);
void freePackageContext(PackageContext *context);
void freeParameterListContext(ParameterListContext *context);
void freeProgramContext(ProgramContext *context);

#endif
