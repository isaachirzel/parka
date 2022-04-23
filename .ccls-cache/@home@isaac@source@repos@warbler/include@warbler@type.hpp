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
		Assignment,
		Expression,
		Block,
		Declaration,
		If
	};

	enum class PrimitiveType
	{
		Integer,
		Unsigned,
		Binary,
		Float,
		Bool,
		Char,
		Str
	};

	enum class ExpressionType
	{
		conditional,
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
		String,
		Integer,
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

	enum class SymbolType
	{
		Function,
		Variable,
		Parameter,
		TypeDefinition
	};
}

#endif
