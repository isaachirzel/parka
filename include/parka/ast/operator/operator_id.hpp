#ifndef PARKA_AST_OPERATOR_OPERATOR_HPP
#define PARKA_AST_OPERATOR_OPERATOR_HPP

#include "parka/ast/type/type_id.hpp"

enum class OperatorType
{
	Add
};

class OperatorId
{
	OperatorType _operatorType;
	TypeId _leftType;
	TypeId _rightType;

	OperatorId(OperatorType operatorType, TypeId leftType, TypeId rightType) :
	_operatorType(operatorType),
	_leftType(leftType),
	_rightType(rightType)
	{}
	OperatorId(OperatorId&&) = default;
	OperatorId(const OperatorId&) = default;
	~OperatorId() = default;

	const auto& operatorType() const { return _operatorType; }
	const auto& entityType() const { return _entityType; }
	const auto& index() const { return _index; }
};

#endif
