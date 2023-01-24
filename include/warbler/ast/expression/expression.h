#ifndef WARBLER_AST_EXPRESSION_H
#define WARBLER_AST_EXPRESSION_H

#include "warbler/ast/type.h"
#include "warbler/symbol_table.h"

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
struct IfExpression;
struct Identifier;

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
		struct Identifier *identifier;
	};

	ExpressionType type;
} Expression;

bool parseExpression(Expression *out, Token *token);
bool validateExpression(Expression *node, LocalSymbolTable *localTable);
bool parsePrimaryExpression(Expression *out, Token *token);
void expressionFree(Expression *node);
Token expressionGetToken(const Expression *node);
bool expressionGetType(Type *out, Expression *node, const Type *expected);

#endif
