#ifndef WARBLER_AST_EXPRESSION_H
#define WARBLER_AST_EXPRESSION_H

#include "warbler/ast/type.h"
#include "warbler/symbol.h"
#include "warbler/token.h"
#include "warbler/util/primitives.h"

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

struct Statement;

typedef enum AssignmentType
{
	ASSIGNMENT_BECOME,
	ASSIGNMENT_MULTIPLY,
	ASSIGNMENT_DIVIDE,
	ASSIGNMENT_MODULUS,
	ASSIGNMENT_ADD,
	ASSIGNMENT_SUBTRACT,
	ASSIGNMENT_LEFT_BIT_SHIFT,
	ASSIGNMENT_RIGHT_BIT_SHIFT,
	ASSIGNMENT_BITWISE_AND,
	ASSIGNMENT_BITWISE_OR,
	ASSIGNMENT_BITWISE_XOR
} AssignmentType;

typedef enum IfType
{
	IF_THEN,
	IF_THEN_ELSE,
	IF_THEN_ELSE_IF
} IfType;

typedef enum LoopType
{
	LOOP_FOR,
	LOOP_WHILE,
	LOOP
} LoopType;

typedef enum JumpType
{
	JUMP_CONTINUE,
	JUMP_BREAK,
	JUMP_RETURN,
	JUMP_YIELD
} JumpType;

typedef enum StatementType
{
	STATEMENT_EXPRESSION,
	STATEMENT_DECLARATION,
	STATEMENT_JUMP
} StatementType;

typedef enum ExpressionType
{
	EXPRESSION_BLOCK,
	EXPRESSION_ASSIGNMENT,
	EXPRESSION_CONDITIONAL,
	EXPRESSION_BOOLEAN_OR,
	EXPRESSION_BOOLEAN_AND,
	EXPRESSION_BITWISE_OR,
	EXPRESSION_BITWISE_XOR,
	EXPRESSION_BITWISE_AND,
	EXPRESSION_EQUALITY,
	EXPRESSION_RELATIONAL,
	EXPRESSION_SHIFT,
	EXPRESSION_ADDITIVE,
	EXPRESSION_MULTIPLICATIVE,
	EXPRESSION_POSTFIX,
	EXPRESSION_PREFIX,
	EXPRESSION_LITERAL,
	EXPRESSION_IDENTIFIER
} ExpressionType;

typedef enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
} AdditiveType;

typedef enum EqualityType
{
	EQUALITY_EQUALS,
	EQUALITY_NOT_EQUALS
} EqualityType;

typedef enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS
} MultiplicativeType;

typedef enum RelationalType
{
	RELATIONAL_GREATER_THAN,
	RELATIONAL_LESS_THAN,
	RELATIONAL_GREATER_THAN_OR_EQUAL_TO,
	RELATIONAL_LESS_THAN_OR_EQUAL_TO
} RelationalType;

typedef enum PostfixType
{
	POSTFIX_INDEX,
	POSTFIX_FUNCTION_CALL,
	POSTFIX_MEMBER
} PostfixType;

typedef enum PrefixType
{
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE,
	PREFIX_POSITIVE,
	PREFIX_NEGATIVE,
	PREFIX_BITWISE_NOT,
	PREFIX_BOOLEAN_NOT
} PrefixType;

typedef enum BitShiftType
{
	BIT_SHIFT_LEFT,
	BIT_SHIFT_RIGHT
} BitShiftType;


typedef struct Identifier
{
	Token token;
	usize index;
	SymbolType type;
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

typedef struct Block
{
	struct Statement* statements;
	usize count;
	Type returnType;
	bool hasReturnType;
} Block;

typedef struct Assignment
{
	Expression lhs;
	Expression rhs;
	AssignmentType type;
} Assignment;

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

typedef struct BooleanOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanOrExpression;

typedef struct BooleanAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanAndExpression;

typedef struct BitwiseOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseOrExpression;

typedef struct BitwiseXorExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseXorExpression;

typedef struct BitwiseAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseAndExpression;

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

typedef struct Prefix
{
	Token token;
	Expression expression;
	PrefixType type;
} Prefix;

typedef struct CallExpression
{
	Expression *expressions;
	usize count;
} CallExpression;

typedef struct Postfix
{
	Expression expression;
	union
	{
		Expression index;
		CallExpression call;
		Token member;
	};
	PostfixType type;
} Postfix;

typedef struct IfExpression
{
	Expression condition;
	struct Statement *thenCase;

	union
	{
		struct Statement *elseCase;
		struct IfExpression *elseIf;
	};

	IfType type;
} IfStatement;

void expressionFree(Expression *node);
void conditionalExpressionFree(ConditionalExpression *node);
void booleanAndExpressionFree(BooleanAndExpression *node);
void bitwiseOrExpressionFree(BitwiseOrExpression *node);
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
void ifExpressionFree(IfStatement *node);
void blockFree(Block *node);
void assignmentFree(Assignment *node);
void callExpressionFree(CallExpression *node);

Token tokenFromExpression(Expression *expression);

#endif
