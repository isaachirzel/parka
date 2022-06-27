#ifndef WARBLER_TYPE_HPP
#define WARBLER_TYPE_HPP

namespace warbler
{
	enum class TypeDefinitionType
	{
		Struct
	};

	enum class AssignmentType
	{
		Become,
		Multiply,
		Divide,
		Modulus,
		Add,
		Subtract,
		LeftBitShift,
		RightBitShift,
		BitwiseAnd,
		BitwiseOr,
		BitwiseXor
	};

	enum class IfType
	{
		Then,
		ThenElse,
		ThenElseIf
	};

	enum class LoopType
	{
		For,
		While,
		Loop
	};

	enum class JumpType
	{
		Continue,
		Break,
		Return,
		Yield
	};

	enum class StatementType
	{
		Expression,
		Declaration,
		Block
	};

	enum class PrimitiveType
	{
		SignedInteger,
		UnsignedInteger,
		FloatingPoint,
		Boolean,
		Character,
		StringLiteral
	};

	enum class ExpressionType
	{
		Assignment,
		Conditional,
		BooleanOr,
		BooleanAnd,
		BitwiseOr,
		BitwiseXor,
		BitwiseAnd,
		Equality,
		Relational,
		Shift,
		Additive,
		Multiplicative,
		Postfix,
		Prefix,
		Primary,
		Constant,
		Symbol
	};

	enum class AdditiveType
	{
		Add,
		Subtract
	};

	enum class ConstantType
	{
		Character,
		StringLiteral,
		SignedInteger,
		UnsignedInteger,
		Float,
		Boolean
	};

	enum class EqualityType
	{
		Equals,
		NotEquals
	};

	enum class MultiplicativeType
	{
		Multiply,
		Divide,
		Modulus
	};

	enum class RelationalType
	{
		GreaterThan,
		LessThan,
		GreaterThanOrEqualTo,
		LessThanOrEqualTo
	};

	enum class PostfixType
	{
		Index,
		FunctionCall,
		Member
	};

	enum class PrefixType
	{
		Reference,
		Dereference,
		Positive,
		Negative,
		BitwiseNot,
		BooleanNot
	};

	enum class BitShiftType
	{
		Left,
		Right
	};

	enum class AnnotationType
	{
		Struct,
		Primitive
	};

	enum class SymbolType
	{
		Package,
		Struct,
		Primitive,
		Function,
		Variable,
		Parameter
	};
}

#endif
