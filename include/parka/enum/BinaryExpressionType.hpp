#ifndef PARKA_ENUM_BINARY_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_BINARY_EXPRESSION_TYPE_HPP

#include <ostream>
namespace parka
{
	enum class BinaryExpressionType
	{
		// Additive
		Add,
		Subtract,

		// Multiplicative
		Multiply,
		Divide,
		Modulus,

		// Logical
		BooleanOr,
		BooleanAnd,

		// Bitwise
		BitwiseOr,
		BitwiseXor,
		BitwiseAnd,

		// Equality
		Equals,
		NotEquals,

		// Relational
		LessThan,
		GreaterThan,
		LessThanOrEqualTo,
		GreaterThanOrEqualTo,
		
		// Shift
		LeftShift,
		RightShift
	};

	std::ostream& operator<<(std::ostream& out, const BinaryExpressionType& binaryExpressionType);
}

#endif
