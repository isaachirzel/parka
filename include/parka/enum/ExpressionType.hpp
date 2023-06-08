#ifndef PARKA_ENUM_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_EXPRESSION_TYPE_HPP

#include <ostream>

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
		Identifier,
		If,
		Subscript,
		MemberAccess,
		Multiplicative,
		Prefix,
		Relational,
		Shift,
		BoolLiteral,
		CharLiteral,
		FloatLiteral,
		IntegerLiteral,
		StringLiteral
	};

	std::ostream& operator<<(std::ostream& out, const ExpressionType& type);
}

#endif
