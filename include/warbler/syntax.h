#ifndef WARBLER_SYNTAX_H
#define WARBLER_SYNTAX_H

#include <warbler/token.h>
#include <warbler/type.h>
#include <warbler/util/table.h>

struct ConditionalExpressionSyntax;
struct BooleanOrExpressionSyntax;
struct BooleanAndExpressionSyntax;
struct BitwiseOrExpressionSyntax;
struct BitwiseXorExpressionSyntax;
struct BitwiseAndExpressionSyntax;
struct EqualityExpressionSyntax;
struct RelationalExpressionSyntax;
struct BitShiftExpressionSyntax;
struct AdditiveExpressionSyntax;
struct MultiplicativeExpressionSyntax;
struct PrefixExpressionSyntax;
struct PostfixExpressionSyntax;
struct ConstantSyntax;
struct SymbolSyntax;
struct AssignmentSyntax;
struct BlockSyntax;
struct DeclarationSyntax;
struct IfStatementSyntax;

typedef struct SymbolSyntax
{
	Token token;
} SymbolSyntax;

typedef struct ExpressionSyntax
{
	union
	{
		struct BlockSyntax *block;
		struct AssignmentSyntax *assignment;
		struct ConditionalExpressionSyntax *conditional;
		struct BooleanOrExpressionSyntax *booleanOr;
		struct BooleanAndExpressionSyntax *booleanAnd;
		struct BitwiseOrExpressionSyntax *bitwiseOr;
		struct BitwiseXorExpressionSyntax *bitwiseXor;
		struct BitwiseAndExpressionSyntax *bitwiseAnd;
		struct EqualityExpressionSyntax *equality;
		struct RelationalExpressionSyntax *relational;
		struct BitShiftExpressionSyntax *shift;
		struct AdditiveExpressionSyntax *additive;
		struct MultiplicativeExpressionSyntax *multiplicative;
		struct PrefixExpressionSyntax *prefix;
		struct PostfixExpressionSyntax *postfix;
		struct ConstantSyntax *constant;
		struct SymbolSyntax *symbol;
	};
	ExpressionType type;
} ExpressionSyntax;

typedef struct ConstantSyntax
{
	Token token;

	union
	{
		char character;
		char *string;
		u64 integer;
		double floating;
		bool boolean;
	};
	ConstantType type;
} ConstantSyntax;

typedef struct ArgumentListSyntax
{
	ExpressionSyntax *expressions;
	usize count;
} ArgumentListSyntax;

typedef struct PostfixExpressionSyntax
{
	ExpressionSyntax expression;
	union
	{
		ExpressionSyntax index;
		ArgumentListSyntax arguments;
		Token member;
	};
	PostfixType type;
} PostfixExpressionSyntax;

typedef struct PrefixExpressionSyntax
{
	Token token;
	ExpressionSyntax expression;
	PrefixType type;
} PrefixExpressionSyntax;

typedef struct MultiplicativeRhsSyntax
{
	ExpressionSyntax expr;
	MultiplicativeType type;
} MultiplicativeRhsSyntax;

typedef struct MultiplicativeExpressionSyntax
{
	ExpressionSyntax lhs;
	MultiplicativeRhsSyntax* rhs;
	usize rhsCount;
} MultiplicativeExpressionSyntax;

typedef struct AdditiveRhsSyntax
{
	ExpressionSyntax expr;
	AdditiveType type;
} AdditiveRhsSyntax;

typedef struct AdditiveExpressionSyntax
{
	ExpressionSyntax lhs;
	AdditiveRhsSyntax *rhs;
	usize rhsCount;
} AdditiveExpressionSyntax;

typedef struct BitShiftRhsSyntax
{
	ExpressionSyntax expr;
	BitShiftType type;
} BitShiftRhsSyntax;

typedef struct BitShiftExpressionSyntax
{
	ExpressionSyntax lhs;
	BitShiftRhsSyntax* rhs;
	usize rhsCount;
} BitShiftExpressionSyntax;

typedef struct RelationalRhsSyntax
{
	ExpressionSyntax expr;
	RelationalType type;
} RelationalRhsSyntax;

typedef struct RelationalExpressionSyntax
{
	ExpressionSyntax lhs;
	RelationalRhsSyntax* rhs;
	usize rhsCount;
} RelationalExpressionSyntax;

typedef struct EqualityRhsSyntax
{
	ExpressionSyntax expr;
	EqualityType type;
} EqualityRhsSyntax;

typedef struct EqualityExpressionSyntax
{
	ExpressionSyntax lhs;
	EqualityRhsSyntax* rhs;
	usize rhsCount;
} EqualityExpressionSyntax;

typedef struct BitwiseAndExpressionSyntax
{
	ExpressionSyntax lhs;
	ExpressionSyntax* rhs;
	usize rhsCount;
} BitwiseAndExpressionSyntax;

typedef struct BitwiseXorExpressionSyntax
{
	ExpressionSyntax lhs;
	ExpressionSyntax* rhs;
	usize rhsCount;
} BitwiseXorExpressionSyntax;

typedef struct BitwiseOrExpressionSyntax
{
	ExpressionSyntax lhs;
	ExpressionSyntax* rhs;
	usize rhsCount;
} BitwiseOrExpressionSyntax;
void freeBitwiseOrExpressionSyntax(BitwiseOrExpressionSyntax *syntax);
typedef struct BooleanAndExpressionSyntax
{
	ExpressionSyntax lhs;
	ExpressionSyntax* rhs;
	usize rhsCount;
} BooleanAndExpressionSyntax;
void freeBooleanAndExpressionSyntax(BooleanAndExpressionSyntax *syntax);
typedef struct BooleanOrExpressionSyntax
{
	ExpressionSyntax lhs;
	ExpressionSyntax* rhs;
	usize rhsCount;
} BooleanOrExpressionSyntax;

typedef struct ConditionalRhsSyntax
{
	ExpressionSyntax trueCase;
	ExpressionSyntax falseCase;
} ConditionalRhsSyntax;

typedef struct ConditionalExpressionSyntax
{
	ExpressionSyntax expression;
	ConditionalRhsSyntax rhs;
	bool hasRhs;
} ConditionalExpressionSyntax;

typedef struct PtrSyntax
{
	Token token;
	bool isMutable;
} PtrSyntax;

typedef struct TypeSyntax
{
	Token name;
	PtrSyntax* ptrs;
	usize ptrCount;
} TypeSyntax;

typedef struct MemberSyntax
{
	Token name;
	TypeSyntax type;
	bool isPublic;
} MemberSyntax;

typedef struct StructSyntax
{
	Token name;
	MemberSyntax* members;
	usize memberCount;
} StructSyntax;

typedef struct VariableSyntax
{
	Token name;
	TypeSyntax type;
	bool isExplicitlyTyped;
	bool isMutable;
} VariableSyntax;

typedef struct StatementSyntax
{
	union
	{
		struct ExpressionSyntax *expression;
		struct DeclarationSyntax *declaration;
	};

	bool isDeclaration;
} StatementSyntax;

typedef struct BlockSyntax
{
	StatementSyntax* statements;
	usize count;
} BlockSyntax;

typedef struct IfStatementSyntax
{
	ExpressionSyntax condition;
	BlockSyntax thenBody;
	union
	{
		BlockSyntax elseBody;
		struct IfStatementSyntax *elseIf;
	};
	IfType type;
} IfStatementSyntax;

typedef struct DeclarationSyntax
{
	VariableSyntax variable;
	ExpressionSyntax value;
} DeclarationSyntax;

typedef struct AssignmentSyntax
{
	ExpressionSyntax lhs;
	ExpressionSyntax rhs;
	AssignmentType type;
} AssignmentSyntax;

typedef struct ParameterSyntax
{
	Token name;
	TypeSyntax type;
	bool isMutable;
} ParameterSyntax;

typedef struct ParameterListSyntax
{
	ParameterSyntax *data;
	usize count;
} ParameterListSyntax;

typedef struct FunctionSyntax
{
	Token name;
	ParameterListSyntax parameters;
	TypeSyntax returnType;
	ExpressionSyntax body;
	bool hasReturnType;
} FunctionSyntax;

typedef struct ModuleSyntax
{
	FunctionSyntax* functions;
	usize functionCount;
	StructSyntax* structs;
	usize structCount;
} ModuleSyntax;

typedef struct PackageSyntax
{
	char *name;
	ModuleSyntax *modules;
	usize moduleCount;
} PackageSyntax;

typedef struct ProgramSyntax
{
	PackageSyntax *packages;
	usize packageCount;
} ProgramSyntax;

// void freeSymbolSyntax(SymbolSyntax *syntax);
void freeExpressionSyntax(ExpressionSyntax *syntax);
void freeConstantSyntax(ConstantSyntax *syntax);
void freeArgumentListSyntax(ArgumentListSyntax *syntax);
void freePostfixExpressionSyntax(PostfixExpressionSyntax *syntax);
void freePrefixExpressionSyntax(PrefixExpressionSyntax *syntax);
void freeMultiplicativeExpressionSyntax(MultiplicativeExpressionSyntax *syntax);
void freeAdditiveExpressionSyntax(AdditiveExpressionSyntax *syntax);
void freeBitShiftExpressionSyntax(BitShiftExpressionSyntax *syntax);
void freeRelationalExpressionSyntax(RelationalExpressionSyntax *syntax);
void freeEqualityExpressionSyntax(EqualityExpressionSyntax *syntax);
void freeBitwiseAndExpressionSyntax(BitwiseAndExpressionSyntax *syntax);
void freeBitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax *syntax);
void freeBooleanOrExpressionSyntax(BooleanOrExpressionSyntax *syntax);
void freeConditionalExpressionSyntax(ConditionalExpressionSyntax *syntax);
void freeTypeSyntax(TypeSyntax *syntax);
void freeMemberSyntax(MemberSyntax *syntax);
void freeStructSyntax(StructSyntax *syntax);
void freeVariableSyntax(VariableSyntax *syntax);
void freeStatementSyntax(StatementSyntax *syntax);
void freeBlockSyntax(BlockSyntax *syntax);
void freeIfStatementSyntax(IfStatementSyntax *syntax);
void freeDeclarationSyntax(DeclarationSyntax *syntax);
void freeAssignmentSyntax(AssignmentSyntax *syntax);
void freeParameterListSyntax(ParameterListSyntax * syntax);
void freeParameterSyntax(ParameterSyntax *syntax);
void freeFunctionSyntax(FunctionSyntax *syntax);
void freeModuleSyntax(ModuleSyntax *syntax);
void freePackageSyntax(PackageSyntax *syntax);
void freeProgramSyntax(ProgramSyntax *syntax);

#endif
