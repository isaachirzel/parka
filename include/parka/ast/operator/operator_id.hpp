#ifndef PARKA_AST_OPERATOR_OPERATOR_HPP
#define PARKA_AST_OPERATOR_OPERATOR_HPP

#include "parka/util/primitives.hpp"

enum class OperatorType
{
	Add
};

class OperatorId
{
	OperatorType _type;
	u32 _index;

public:

	OperatorId(OperatorType type, u32 index) :
	_type(type),
	_index(index)
	{}
	OperatorId(OperatorId&&) = default;
	OperatorId(const OperatorId&) = default;
	~OperatorId() = default;

	const auto& type() const { return _type; }
	const auto& index() const { return _index; }
};


#endif
