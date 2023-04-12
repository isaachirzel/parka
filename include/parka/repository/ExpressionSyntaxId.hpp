#ifndef PARKA_ENTITY_EXPRESSION_ID_HPP
#define PARKA_ENTITY_EXPRESSION_ID_HPP

#include "parka/util/Common.hpp"

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

	class ExpressionSyntaxId
	{
		usize _index;
		ExpressionType _type;

		ExpressionSyntaxId(ExpressionType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:
		
		ExpressionSyntaxId(ExpressionSyntaxId&&) = default;
		ExpressionSyntaxId(const ExpressionSyntaxId&) = default;
		~ExpressionSyntaxId() = default;
		ExpressionSyntaxId& operator=(ExpressionSyntaxId&&) = default;
		ExpressionSyntaxId& operator=(const ExpressionSyntaxId&) = default;

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }

		friend struct SyntaxRepository;
	};
}

#endif
