#ifndef PARKA_ENUM_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_EXPRESSION_TYPE_HPP

namespace parka
{
	enum class ExpressionType
	{
		Additive,
		Assignment,
		BitwiseAnd,
		BitwiseOr,
		BitwiseXor,
		Block,
		BooleanAnd,
		BooleanOr,
		Call,
		Conditional,
		Equality,
		IdentifierExpression,
		If,
		Subscript,
		MemberAccessExpression,
		Multiplicative,
		PrefixExpression,
		Relational,
		Shift,
		BoolLiteral,
		CharLiteral,
		FloatLiteral,
		IntegerLiteral,
		StringLiteral
	};

	// TODO: Create print function
}

#endif
