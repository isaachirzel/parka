#ifndef PARKA_ENTITY_EXPRESSION_ID_HPP
#define PARKA_ENTITY_EXPRESSION_ID_HPP

#include "parka/util/Primitives.hpp"

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
		IdentifierExpressionSyntax,
		If,
		Subscript,
		MemberAccessExpressionSyntax,
		Multiplicative,
		PrefixExpressionSyntax,
		Relational,
		Shift,
		BoolLiteralSyntax,
		CharLiteralSyntax,
		FloatLiteralSyntax,
		IntegerLiteralSyntax,
		StringLiteralSyntax
	};

	class ExpressionId
	{
		usize _index;
		ExpressionType _type;

		ExpressionId(ExpressionType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:
		
		ExpressionId(ExpressionId&&) = default;
		ExpressionId(const ExpressionId&) = default;
		~ExpressionId() = default;
		ExpressionId& operator=(ExpressionId&&) = default;
		ExpressionId& operator=(const ExpressionId&) = default;

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }

		friend struct Storage;
	};
}

#endif
