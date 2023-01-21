#ifndef WARBLER_AST_H
#define WARBLER_AST_H

#include "warbler/token.h"
#include "warbler/type.h"
#include "warbler/symbol_id.h"

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
struct Assignment;
struct Block;
struct Declaration;
struct IfExpression;

typedef struct Primitive
{
	const char *symbol;
	PrimitiveType type;
	u32 size;
} Primitive;

typedef struct Identifier
{
	Token token;
	usize id;
} Identifier;

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
		Identifier identifier;
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
	usize index;
	SymbolType type;
	// TODO: Add pointer info
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
		struct JumpStatement *jump;
	};

	StatementType type;
} Statement;

typedef struct Block
{
	Statement* statements;
	usize count;
	Type returnType;
	bool hasReturnType;
} Block;

typedef struct IfExpression
{
	Expression condition;
	Statement thenCase;

	union
	{
		Statement elseCase;
		struct IfExpression *elseIf;
	};

	IfType type;
} IfStatement;

typedef struct JumpStatement
{
	Token token;
	JumpType type;
	Expression value;
	bool hasValue;
} JumpStatement;

typedef struct Declaration
{
	usize variableId;
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
	IdList parameterIds;
	TypeAnnotation returnType;
	Expression body;
	bool hasReturnType;
} Function;

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

extern const usize voidSymbolId;
extern const usize u8SymbolId;
extern const usize u16SymbolId;
extern const usize u32SymbolId;
extern const usize u64SymbolId;
extern const usize i8SymbolId;
extern const usize i16SymbolId;
extern const usize i32SymbolId;
extern const usize i64SymbolId;
extern const usize f32SymbolId;
extern const usize f64SymbolId;
extern const usize boolSymbolId;
extern const usize charSymbolId;
extern const usize stringSymbolId;
extern const Type voidType;
extern const Primitive primitives[];
extern const usize primitiveCount;

void booleanAndExpressionFree(BooleanAndExpression *node);
void bitwiseOrExpressionFree(BitwiseOrExpression *node);
void expressionFree(Expression *node);
void literalFree(Literal *node);
void argumentListFree(ArgumentList *node);
void postfixExpressionFree(Postfix *node);
void prefixExpressionFree(Prefix *node);
void multiplicativeExpressionFree(MultiplicativeExpression *node);
void additiveExpressionFree(AdditiveExpression *node);
void bitShiftExpressionFree(BitShiftExpression *node);
void relationalExpressionFree(RelationalExpression *node);
void equalityExpressionFree(EqualityExpression *node);
void bitwiseAndExpressionFree(BitwiseAndExpression *node);
void bitwiseXorExpressionFree(BitwiseXorExpression *node);
void booleanOrExpressionFree(BooleanOrExpression *node);
void conditionalExpressionFree(ConditionalExpression *node);
void typeAnnotationFree(TypeAnnotation *node);
void memberFree(Member *node);
void memberListFree(MemberList *node);
void structFree(Struct *node);
void variableFree(Local *node);
void statementFree(Statement *node);
void jumpStatementFree(JumpStatement *node);
void blockFree(Block *node);
void ifExpressionFree(IfStatement *node);
void declarationFree(Declaration *node);
void assignmentFree(Assignment *node);
void parameterFree(Local *node);
void functionFree(Function *node);
void moduleFree(Module *node);
void packageFree(Package *node);

Token tokenFromExpression(Expression *expression);
Type typeFromExpression(Expression *expression, const Type *expectedType);
Type typeDuplicate(const Type *type);
bool typeCanConvert(const Type *to, const Type *from);

/**
 * @return Malloc'd string representation of type
 */
char *typeGetName(const Type *type);
const Type *functionGetReturnType(const Function *function);

#endif
