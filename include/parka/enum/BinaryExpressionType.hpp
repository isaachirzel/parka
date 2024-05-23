#ifndef PARKA_ENUM_BINARY_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_BINARY_EXPRESSION_TYPE_HPP

#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	enum class BinaryExpressionType: u8
	{
		// Additive
		Add,
		Subtract,

		// Multiplicative
		Multiply,
		Divide,
		Modulus,

		// Bitwise
		BitwiseOr,
		BitwiseXor,
		BitwiseAnd,
		
		// Shift
		LeftShift,
		RightShift,

		// Relational
		LessThan,
		GreaterThan,
		LessThanOrEqualTo,
		GreaterThanOrEqualTo,

		// Equality
		Equals,
		NotEquals,
		
		// Logical
		BooleanOr,
		BooleanAnd,
	};

	std::ostream& operator<<(std::ostream& out, const BinaryExpressionType& binaryExpressionType);
}

#endif
