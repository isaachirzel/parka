#ifndef WARBLER_AST_H
#define WARBLER_AST_H

#include <warbler/token.h>
#include <warbler/type.h>
#include <warbler/symbol_id.h>

struct ConditionalExpression;
struct BooleanOrExpression;
struct BooleanAndExpression;
struct BitwiseOrExpression;
struct BitwiseXorExpression;
struct BitwiseAndExpression;
struct EqualityExpression;
struct RelationalExpression;
struct BitShiftExpression;
struct AdditiveExpression;
struct MultiplicativeExpression;
struct Prefix;
struct Postfix;
struct Literal;
struct Symbol;
struct Assignment;
struct Block;
struct Declaration;
struct IfStatement;

typedef struct Primitive
{
	const char *symbol;
	PrimitiveType type;
	u32 size;
} Primitive;

typedef struct Symbol
{
	Token token;
	SymbolId id;
} Symbol;

typedef struct Expression
{
	union
	{
		struct Block *block;
		struct Assignment *assignment;
		struct ConditionalExpression *conditional;
		struct BooleanOrExpression *booleanOr;
		struct BooleanAndExpression *booleanAnd;
		struct BitwiseOrExpression *bitwiseOr;
		struct BitwiseXorExpression *bitwiseXor;
		struct BitwiseAndExpression *bitwiseAnd;
		struct EqualityExpression *equality;
		struct RelationalExpression *relational;
		struct BitShiftExpression *shift;
		struct AdditiveExpression *additive;
		struct MultiplicativeExpression *multiplicative;
		struct Prefix *prefix;
		struct Postfix *postfix;
		struct Literal *literal;
		Symbol symbol;
	};

	ExpressionType type;
} Expression;

typedef struct StringLiteral
{
	char *text;
	usize length;
} StringLiteral;

typedef struct IntegerLiteral
{
	u64 integer;
	usize minBits;
} IntegerLiteral;

typedef struct Literal
{
	Token token;

	union
	{
		char character;
		StringLiteral string;
		IntegerLiteral integer;
		double floating;
		bool boolean;
	};

	LiteralType type;
} Literal;

typedef struct ArgumentList
{
	Expression *expressions;
	usize count;
} ArgumentList;

typedef struct Postfix
{
	Expression expression;
	union
	{
		Expression index;
		ArgumentList arguments;
		Token member;
	};
	PostfixType type;
} Postfix;

typedef struct Prefix
{
	Token token;
	Expression expression;
	PrefixType type;
} Prefix;

typedef struct MultiplicativeRhs
{
	Expression expr;
	MultiplicativeType type;
} MultiplicativeRhs;

typedef struct MultiplicativeExpression
{
	Expression lhs;
	MultiplicativeRhs* rhs;
	usize rhsCount;
} MultiplicativeExpression;

typedef struct AdditiveRhs
{
	Expression expr;
	AdditiveType type;
} AdditiveRhs;

typedef struct AdditiveExpression
{
	Expression lhs;
	AdditiveRhs *rhs;
	usize rhsCount;
} AdditiveExpression;

typedef struct BitShiftRhs
{
	Expression expr;
	BitShiftType type;
} BitShiftRhs;

typedef struct BitShiftExpression
{
	Expression lhs;
	BitShiftRhs* rhs;
	usize rhsCount;
} BitShiftExpression;

typedef struct RelationalRhs
{
	Expression expr;
	RelationalType type;
} RelationalRhs;

typedef struct RelationalExpression
{
	Expression lhs;
	RelationalRhs* rhs;
	usize rhsCount;
} RelationalExpression;

typedef struct EqualityRhs
{
	Expression expr;
	EqualityType type;
} EqualityRhs;

typedef struct EqualityExpression
{
	Expression lhs;
	EqualityRhs* rhs;
	usize rhsCount;
} EqualityExpression;

typedef struct BitwiseAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseAndExpression;

typedef struct BitwiseXorExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseXorExpression;

typedef struct BitwiseOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseOrExpression;

typedef struct BooleanAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanAndExpression;

typedef struct BooleanOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanOrExpression;

typedef struct ConditionalRhs
{
	Expression trueCase;
	Expression falseCase;
} ConditionalRhs;

typedef struct ConditionalExpression
{
	Expression expression;
	ConditionalRhs rhs;
	bool hasRhs;
} ConditionalExpression;

typedef struct Type
{
	SymbolId id;
	// Ptrs
} Type;

typedef struct TypeAnnotation
{
	Token token;
	Type type;
} TypeAnnotation;

typedef struct Member
{
	Token name;
	char *symbol;
	TypeAnnotation annotation;
	bool isPublic;
} Member;

typedef struct MemberList
{
	Member *data;
	usize count;
} MemberList;

typedef struct Local
{
	Token name;
	char *symbol;
	TypeAnnotation type;
	bool isMutable;
	bool isExplicitlyTyped;
} Local;

typedef struct Struct
{
	Token name;
	char *symbol;
	MemberList members;
} Struct;

typedef struct Statement
{
	union
	{
		struct Expression *expression;
		struct Declaration *declaration;
	};

	bool isDeclaration;
} Statement;

typedef struct Block
{
	Statement* statements;
	usize count;
	TypeAnnotation returnType;
	bool hasReturnType;
} Block;

typedef struct IfStatement
{
	Expression condition;
	Block thenBody;

	union
	{
		Block elseBody;
		struct IfStatement *elseIf;
	};

	IfType type;
} IfStatement;

typedef struct Declaration
{
	SymbolId variableId;
	Expression value;
} Declaration;

typedef struct Assignment
{
	Expression lhs;
	Expression rhs;
	AssignmentType type;
} Assignment;

typedef struct Operator
{
	Type leftType;
	Type rightType;
	Type returnType;
} Operator;

typedef struct Function
{
	Token name;
	char *symbol;
	SymbolIdList parameterIds;
	TypeAnnotation returnType;
	Expression body;
	bool hasReturnType;
} Function;

typedef struct Module
{
	char *symbol;
	SymbolIdList functionIds;
	SymbolIdList structIds;
} Module;

typedef struct Package
{
	char *symbol;
	Module *modules;
	usize moduleCount;
} Package;

extern SymbolId voidSymbolId;
extern SymbolId u8SymbolId;
extern SymbolId u16SymbolId;
extern SymbolId u32SymbolId;
extern SymbolId u64SymbolId;
extern SymbolId uFlexSymbolId;
extern SymbolId i8SymbolId;
extern SymbolId i16SymbolId;
extern SymbolId i32SymbolId;
extern SymbolId i64SymbolId;
extern SymbolId iFlexSymbolId;
extern SymbolId f32SymbolId;
extern SymbolId f64SymbolId;
extern SymbolId boolSymbolId;
extern SymbolId charSymbolId;
extern SymbolId stringSymbolId;
extern const Primitive primitives[];
extern const usize primitiveCount;

// void freeSymbol(Symbol *node);
void freeSymbolIdList(SymbolIdList *node);
void freeBooleanAndExpression(BooleanAndExpression *node);
void freeBitwiseOrExpression(BitwiseOrExpression *node);
void freeExpression(Expression *node);
void freeLiteral(Literal *node);
void freeArgumentList(ArgumentList *node);
void freePostfixExpression(Postfix *node);
void freePrefixExpression(Prefix *node);
void freeMultiplicativeExpression(MultiplicativeExpression *node);
void freeAdditiveExpression(AdditiveExpression *node);
void freeBitShiftExpression(BitShiftExpression *node);
void freeRelationalExpression(RelationalExpression *node);
void freeEqualityExpression(EqualityExpression *node);
void freeBitwiseAndExpression(BitwiseAndExpression *node);
void freeBitwiseXorExpression(BitwiseXorExpression *node);
void freeBooleanOrExpression(BooleanOrExpression *node);
void freeConditionalExpression(ConditionalExpression *node);
void freeTypeAnnotation(TypeAnnotation *node);
void freeMember(Member *node);
void freeMemberList(MemberList *node);
void freeStruct(Struct *node);
void freeVariable(Local *node);
void freeStatement(Statement *node);
void freeBlock(Block *node);
void freeIfStatement(IfStatement *node);
void freeDeclaration(Declaration *node);
void freeAssignment(Assignment *node);
void freeParameter(Local *node);
void freeFunction(Function *node);
void freeModule(Module *node);
void freePackage(Package *node);

#endif
