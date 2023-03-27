#ifndef PARKA_AST_OPERATOR_HPP
#define PARKA_AST_OPERATOR_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/type.hpp"
#include "parka/util/array.hpp"

enum class OperatorType
{
	Add
};

class Operator
{
	OperatorType type;
	Type rightType;
	Type returnType;
	bool isBuiltIn;
	ExpressionId body;

public:
};

class Operators
{
	Array<Operator> _addOperators;

public:

	const auto& addOperators() const { return _addOperators; }
};

#endif
