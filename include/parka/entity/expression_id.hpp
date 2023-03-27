#ifndef PARKA_ENTITY_EXPRESSION_ID_HPP
#define PARKA_ENTITY_EXPRESSION_ID_HPP

#include "parka/util/primitives.hpp"

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
	Shift
};

class ExpressionId
{
	usize _index;
	ExpressionType _type;

public:
	
	ExpressionId(ExpressionType type, usize index) :
	_index(index),
	_type(type)
	{}
	ExpressionId(ExpressionId&&) = default;
	ExpressionId(const ExpressionId&) = default;
	~ExpressionId() = default;
	ExpressionId& operator=(ExpressionId&&) = default;
	ExpressionId& operator=(const ExpressionId&) = default;

	const auto& index() const { return _index; }
	const auto& type() const { return _type; }
};

#endif
