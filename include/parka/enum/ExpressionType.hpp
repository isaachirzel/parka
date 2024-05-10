#ifndef PARKA_ENUM_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_EXPRESSION_TYPE_HPP

#include <ostream>

namespace parka
{
	enum class ExpressionType
	{
		Binary,
		Call,
		Conditional,
		Identifier,
		If,
		Subscript,
		MemberAccess,
		Prefix,
		BoolLiteral,
		CharLiteral,
		FloatLiteral,
		IntegerLiteral,
		StringLiteral
	};

	std::ostream& operator<<(std::ostream& out, const ExpressionType& type);
}

#endif
