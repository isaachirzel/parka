#ifndef PARKA_ENUM_BINARY_EXPRESSION_TYPE_HPP
#define PARKA_ENUM_BINARY_EXPRESSION_TYPE_HPP

namespace parka
{
	enum class BinaryExpressionType
	{
		// Multiplicative
		Multiply,
		Divide,
		Modulus,

		// Additive
		Add,
		Subtract,

		BooleanOr,
		BooleanAnd,
		BitwiseOr,
		BitwiseXor,
		BitwiseAnd,

		// Assignment
		Assign,
		MultiplyAssign,
		DivideAssign,
		ModulusAssign,
		AddAssign,
		SubtractAssign,
		LeftShiftAssign,
		RightShiftAssign,
		BitwiseAndAssign,
		BitwiseOrAssign,
		BitwiseXorAssign,

		// Equality
		Equals,
		NotEquals,

		// Relational
		GreaterThan,
		LessThan,
		GreaterThanOrEqualTo,
		LessThanOrEqualTo,
		
		// Shift
		LeftShift,
		RightShift
	};
}

#endif
