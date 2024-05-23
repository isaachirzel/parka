#ifndef PARKA_ENUM_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_EXPRESSION_TYPE_HPP

#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	enum class ExpressionType: u8
	{
		Binary,
		Call,
		Conditional,
		Identifier,
		Subscript,
		MemberAccess,
		Prefix,
		Cast,
		BoolLiteral,
		CharLiteral,
		FloatLiteral,
		IntegerLiteral,
		StringLiteral
	};

	std::ostream& operator<<(std::ostream& out, const ExpressionType& type);
}

#endif
