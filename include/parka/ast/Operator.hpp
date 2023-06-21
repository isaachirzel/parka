#ifndef PARKA_AST_FUNCTION_OPERATOR_HPP
#define PARKA_AST_FUNCTION_OPERATOR_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/parser/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class Operator
	{
		ir::ValueType _leftType;
		ir::ValueType _rightType;
		ExpressionAst *_body;
		OperatorType _type;

	public:

		Operator(ir::ValueType&& leftType, ir::ValueType&& rightType, ExpressionAst *body, OperatorType type) :
		_leftType(std::move(leftType)),
		_rightType(std::move(rightType)),
		_body(body),
		_type(type)
		{}

		const auto& leftType() const { return _leftType; }
		const auto& rightType() const { return _rightType; }
		const auto& body() const { return _body; }
		const auto& type() const { return _type; }
	};
}

#endif
